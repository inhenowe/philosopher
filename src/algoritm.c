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
	while (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
	{
		act_of_eat(philo);
		if (mutexcopyi(&philo->mutex_5[EA_C], philo->eat_check) ==
				mutexcopyi(&philo->data->dead, philo->data->must_eat))
		{
			mutextrue(&philo->mutex_5[FULL], &philo->full);
			break ;
		}
		take_a_nap(philo);
		if (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
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
		if (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
			mutexprint(philo, MS1);
	}
	else if ((philo->id % 2) != 0 )
	{
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (!mutexcopyb(&philo->data->dead, philo->data->dead_man))
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
	mutextrue(&philo->mutex_5[SAVE], &philo->save);
	if (!mutexcopyb(&philo->data->dead ,philo->data->dead_man))
		mutexprint(philo, MS2);
	mutexiter(&philo->mutex_5[EA_C], &philo->eat_check);
	pthread_mutex_lock(&philo->mutex_5[T_EA]);
	philo->time_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_5[T_EA]);
	usleep(1000 * philo->data->time_eat_ms);
	pthread_mutex_lock(&philo->mutex_5[SAVE]);
	philo->save = FALSE;
	pthread_mutex_unlock(&philo->mutex_5[SAVE]);
	
}

static void	take_a_nap(t_platon *philo)
{
	if (!mutexcopyb(&philo->data->dead ,philo->data->dead_man))
		mutexprint(philo, MS3);
	usleep(1000 * philo->data->time_eat_ms);
}

void	*scan_cycle(void *param)
{
	t_philo	*data;
	int		i;

	data = (t_philo *)param;
	i = -1;
	usleep(1000);
	while (1)
	{
		i = -1;
		while (++i < data->num_philo)
		{
			if (data->must_eat != -1)
				activate_all_eat(data, i);
			if (!mutexcopyb(&data->dead, data->dead_man) &&
					!mutexcopyb(&data->th[i].mutex_5[FULL],  data->th[i].full) &&
					!mutexcopyb(&data->th[i].mutex_5[SAVE],  data->th[i].save))
				activate_dead(data, i);
		}
		if (mutexcopyb(&data->dead ,data->dead_man) ||
				data->all_eat)
			break ;
		usleep(1000);
	}
	return (NULL);
}
