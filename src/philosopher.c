/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:30:47 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/07 17:15:55 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static void	initdata(t_philo *data);
static void	init_philosophers(t_philo *data);

int	main(int argc, char *argv[])
{
	t_philo	data;
	int		i;

	i = -1;
	initdata(&data);
	if (argcheck(argc - 1, argv + 1, &data))
		exit(1);
	data.time = get_time();
	if (data.num_philo == 1)
	{
		one_case(&data);
		pthread_join(data.th[0].thread, NULL);
	}
	else
	{
		data.time = get_time();
		init_signals(&data.forks, data.num_philo);
		init_philosophers(&data);
		pthread_create(&data.monitor, NULL, &scan_cycle, &data);
		while (++i < data.num_philo)
			pthread_join(data.th[i].thread, NULL);
		pthread_join(data.monitor, NULL);
		free_all(&data);
	}
}

static void	initdata(t_philo *data)
{
	data->num_philo = 0;
	data->time_die_ms = 0;
	data->time_eat_ms = 0;
	data->time_nap_ms = 0;
	data->must_eat = -1;
	data->full_count = 0;
	data->dead_man = FALSE;
	data->all_eat = FALSE;
}

static void	init_philosophers(t_philo *data)
{
	int	i;

	i = -1;
	data->th = malloc(sizeof(t_platon) * data->num_philo);
	if (!data->th)
		return (errorlog("malloc"));
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead, NULL);
	while (++i < data->num_philo)
	{
		init_signals(&data->th[i].mutex_5, 5);
		data->th[i].id = i + 1;
		data->th[i].eat_check = 0;
		data->th[i].data = data;
		data->th[i].full = FALSE;
		data->th[i].check = FALSE;
		data->th[i].save = FALSE;
		data->th[i].time_eat = data->time;
		pthread_create(&data->th[i].thread, NULL, &routine, &data->th[i]);
	}
}

unsigned long	mutexcopyl(pthread_mutex_t *mutex, unsigned long *var)
{
	unsigned long	i;

	pthread_mutex_lock(mutex);
	 i = *var;
	pthread_mutex_unlock(mutex);
	return (i);
}
