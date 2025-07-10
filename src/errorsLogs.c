/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsLogs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:22 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/02 15:19:02 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	errorlog(char *error)
{
	int	i;

	i = 0;
	while (error[i])
		write(2, &error[i++], 1);
	write(2, "\n", 1);
}

void	free_all(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->th);
	free(data->forks);
}
