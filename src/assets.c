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
	if ((get_time() - data->th[i].time_eat) >= (unsigned long)data->time_die_ms
		&& !data->th[i].full)
	{
		mutextrue(&data->signal[S9], &data->dead_man);
		mutexprint(&data->th[i], MS5);
	}
}

void	activate_all_eat(t_philo *data, int i)
{
	pthread_mutex_lock(&data->signal[S7]);
	if (data->th[i].full && !data->th[i].check)
	{
		mutexiter(&data->signal[S4], &data->full_count);
		mutextrue(&data->signal[S5], &data->th[i].check);
	}
	if (data->full_count == data->num_philo)
		mutextrue(&data->signal[S6], &data->all_eat);
	pthread_mutex_unlock(&data->signal[S7]);
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

	data = (t_platon*)param;
	pthread_mutex_lock(&data->data->forks[0]);
	printf(B_M"%lu 1 has taken a fork\n"R, get_time() - data->data->time);
	while ((get_time() - data->data->time) < (unsigned long)data->data->time_die_ms)
		;
	printf(B_R"%lu 1 died\n"R, get_time() - data->data->time);
	pthread_mutex_unlock(&data->data->forks[0]);
	return (NULL);
}

void	init_signals(t_philo *data)
{
	int	i;

	i = -1;
	data->signal = malloc(sizeof(pthread_mutex_t) * 9);
	if (!data->signal)
		return (errorlog("malloc"));
	while (++i < 9)
		pthread_mutex_init(&data->signal[i], NULL);
}