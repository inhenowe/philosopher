/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:09:18 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/07 19:24:25 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	activate_dead(t_philo *data, int i)
{
	if ((get_time() - mutexcopyl(&data->th[i].mutex_5[T_EA],
				&data->th[i].time_eat) >= (unsigned long)data->time_die_ms))
	{
		mutextrue(&data->dead, &data->dead_man);
		mutexprint(&data->th[i], MS5);
	}
}

void	activate_all_eat(t_philo *data, int i)
{
	if (mutexcopyb(&data->th[i].mutex_5[FULL], &data->th[i].full)
		&& !mutexcopyb(&data->th[i].mutex_5[FLAG], &data->th[i].check))
	{
		mutextrue(&data->th[i].mutex_5[FLAG], &data->th[i].check);
		data->full_count++;
	}
	if (data->full_count == mutexcopyi(&data->write, &data->num_philo))
		mutextrue(&data->write, &data->all_eat);
}

void	one_case(t_philo *data)
{
	int	i;

	i = -1;
	data->th = malloc(sizeof(t_platon) * data->num_philo);
	if (!data->th)
		return (errorlog("malloc"));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (free(data->th), errorlog("malloc"));
	while (++i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->num_philo)
	{
		data->th[i].id = i + 1;
		data->th[i].eat_check = 0;
		data->th[i].data = data;
		data->th[i].full = FALSE;
		data->th[i].check = FALSE;
		data->th[i].time_eat = data->time;
		pthread_create(&data->th[i].thread, NULL, &rutone, &data->th[i]);
	}
}

void	*rutone(void *param)
{
	t_platon	*data;

	data = (t_platon *)param;
	pthread_mutex_lock(&data->data->forks[0]);
	printf(B_M"%lu 1 has taken a fork\n"R, get_time() - data->data->time);
	while ((get_time() - data->data->time)
		< (unsigned long)data->data->time_die_ms)
		;
	printf("%lu 1 died\n", get_time() - data->data->time);
	pthread_mutex_unlock(&data->data->forks[0]);
	return (NULL);
}

void	init_signals(pthread_mutex_t **mutex, int num)
{
	int	i;

	i = -1;
	*mutex = malloc(sizeof(pthread_mutex_t) * num);
	if (!*mutex)
		return (errorlog("malloc"));
	while (++i < num)
		pthread_mutex_init(&(*mutex)[i], NULL);
}
