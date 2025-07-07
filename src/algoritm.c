/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:33:06 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/07 17:41:41 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static void	act_of_eat(t_platon *philo);
static void	take_a_nap(t_platon *philo);
static void	eating(t_platon *philo);

void	*routine(void *param)
{
	t_platon	*philo;

	philo = (t_platon *)param;
	while (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
	{
		act_of_eat(philo);
		if (mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			break ;
		if (philo->eat_check == mutexcopyi(&philo->data->signal[S3],philo->data->must_eat))
		{
			mutextrue(&philo->data->signal[S2], &philo->full);
			break ;
		}
		take_a_nap(philo);
		if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			mutexprint(philo, MS4);
		usleep(500);
	}
	return (NULL);
}



static void	act_of_eat(t_platon *philo)
{
	int	l_fork;
	int	r_fork;

	l_fork = philo->id - 1;
	r_fork = philo->id % philo->data->num_philo;
	if ((philo->id % 2) == 0)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		{
			pthread_mutex_unlock(&philo->data->forks[l_fork]);
			return ;
		}
		if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		{
			pthread_mutex_unlock(&philo->data->forks[r_fork]);
			pthread_mutex_unlock(&philo->data->forks[l_fork]);
			return ;
		}
		if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			mutexprint(philo, MS1);
	}
	else if ((philo->id % 2) != 0 || philo->id == mutexcopyi(&philo->data->signal[S3], philo->data->num_philo))
	{
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		{
			pthread_mutex_unlock(&philo->data->forks[r_fork]);
			return ;
		}
		if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		{
			pthread_mutex_unlock(&philo->data->forks[l_fork]);
			pthread_mutex_unlock(&philo->data->forks[r_fork]);
			return ;
		}
		if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
			mutexprint(philo, MS1);
	}
	eating(philo);
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[l_fork]);
		pthread_mutex_unlock(&philo->data->forks[r_fork]);
	}
	if ((philo->id % 2) != 0)
	{
		pthread_mutex_unlock(&philo->data->forks[r_fork]);
		pthread_mutex_unlock(&philo->data->forks[l_fork]);
	}
}

static void	eating(t_platon *philo)
{
	if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		mutexprint(philo, MS2);
	mutexiter(&philo->data->signal[S2], &philo->eat_check);
	pthread_mutex_lock(&philo->data->signal[S8]);
	philo->time_eat = get_time();
	usleep(1000 * philo->data->time_eat_ms);
	pthread_mutex_unlock(&philo->data->signal[S8]);
}

static void	take_a_nap(t_platon *philo)
{
	if (!mutexcopyb(&philo->data->signal[S9], philo->data->dead_man))
		mutexprint(philo, MS3);
	pthread_mutex_lock(&philo->data->signal[S8]);
	usleep(philo->data->time_nap_ms * 1000);
	pthread_mutex_unlock(&philo->data->signal[S8]);
}

void	*scan_cycle(void *param)
{
	t_philo	*data;
	int		i;

	data = (t_philo *)param;
	i = -1;
	while (1)
	{
		i = -1;
		while (++i < data->num_philo)
		{
			if (data->must_eat != -1)
				activate_all_eat(data, i);
			if (!mutexcopyb(&data->signal[S9], data->dead_man))
				activate_dead(data, i);
		}
		if (mutexcopyb(&data->signal[S9], data->dead_man) ||
			mutexcopyb(&data->signal[S7], data->all_eat))
			break ;
		usleep(1000);
	}
	return (NULL);
}