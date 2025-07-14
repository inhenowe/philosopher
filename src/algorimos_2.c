/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorimos_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:36:51 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/07 17:32:35 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	mutexprint(t_platon *phl, const char *msg)
{
	pthread_mutex_lock(&phl->data->write);
	printf(msg, get_time() - phl->data->time, phl->id);
	pthread_mutex_unlock(&phl->data->write);
}

void	mutexiter(pthread_mutex_t *mutex, int *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}

void	mutextrue(pthread_mutex_t *mutex, t_bool *var)
{
	pthread_mutex_lock(mutex);
	(*var) = TRUE;
	pthread_mutex_unlock(mutex);
}

t_bool	mutexcopyb(pthread_mutex_t *mutex, t_bool *var)
{
	t_bool	dead;

	pthread_mutex_lock(mutex);
	dead = *var;
	pthread_mutex_unlock(mutex);
	return (dead);
}

int	mutexcopyi(pthread_mutex_t *mutex, int *var)
{
	int	i;

	pthread_mutex_lock(mutex);
	i = *var;
	pthread_mutex_unlock(mutex);
	return (i);
}
