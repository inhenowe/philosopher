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
// void		mute_all(t_philo *data);

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
		init_philosophers(&data);
		init_signals(&data);
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
		pthread_create(&data->th[i].thread, NULL, &routine, &data->th[i]);
	}
	pthread_create(&data->monitor, NULL, &scan_cycle, &data);
}

// void	mute_all(t_philo *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->num_philo)
// 		pthread_mutex_lock(&data->forks[i]);
// 	pthread_mutex_lock(&data->write);
// 	pthread_mutex_lock(&data->var);
// 	i = -1;
// 	while (++i < data->num_philo)
// 		pthread_mutex_unlock(&data->forks[i]);
// 	pthread_mutex_unlock(&data->write);
// 	pthread_mutex_unlock(&data->var);
// }
