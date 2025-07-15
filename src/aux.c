/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.com>  +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:40:50 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/14 17:43:50 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	take_fork(t_platon *philo, int r_fork, int l_fork)
{
	if ((philo->id % 2) == 0)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
	}
	else if ((philo->id % 2) != 0)
	{
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
	}
}
