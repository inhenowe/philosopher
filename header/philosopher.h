/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:30:29 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/07 17:30:52 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/*-------dependencies-------*/
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

/*-------constants_colors-------*/
# define R "\033[0m"
# define B_N "\033[1;30m"
# define B_R "\033[1;31m"
# define B_G "\033[1;32m"
# define B_Y "\033[1;33m"
# define B_B "\033[1;34m"
# define B_M "\033[1;35m"
# define B_C "\033[1;36m"
# define B_W "\033[1;37m"

/*-------constants_Utilities-------*/
# define MA1 "Error\nPlease insert the data as follows: Philo:x Die:x Eat:x \
Sleep:x Musteat:x"
# define MA2 "Error\nPlease only positive numbers as values"
# define MA3 "Error\nNumber of philosopher wrong"
# define MS1 B_M"%lu %i has taken a fork\n"R
# define MS2 B_G"%lu %i is eating\n"R
# define MS3 B_C"%lu %i is sleeping\n"R
# define MS4 B_Y"%lu %i is thinking\n"R
# define MS5 B_R"%lu %i died\n"R

/*-------mutex_5-------*/
# define EA_C 0
# define FULL 1
# define Tms_EA 2
# define SAVE 3
# define FLAG 4

/*-------define_struct-------*/
typedef struct s_philo	t_philo;

/*-------enum_Utilities-------*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/*-------strcut_philos-------*/
typedef struct s_platon
{
	pthread_t		thread;
	int				id;
	int				eat_check;
	unsigned long	time_eat;
	t_bool			full;
	t_bool			check;
	t_bool			save;
	t_philo			*data;
	pthread_mutex_t	*mutex_5;
}	t_platon;

/*-------struct_data_argu-------*/
typedef struct s_philo
{
	int				num_philo;
	int				time_die_ms;
	int				time_eat_ms;
	int				time_nap_ms;
	int				must_eat;
	int				full_count;
	unsigned long	time;
	t_bool			all_eat;
	t_bool			dead_man;
	t_platon		*th;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
}	t_philo;

/*-------funtion_of_src-------*/
//checkers
t_bool			argcheck(int argc, char **spl, t_philo *data);
void			activate_all_eat(t_philo *data, int i);
void			activate_dead(t_philo *data, int i);
void			one_case(t_philo *data);

//routine_and_data_block
void			*rutone(void *param);
void			*routine(void *param);
void			*scan_cycle(void *param);
void			init_signals(pthread_mutex_t **mutex, int num);
void			mutexiter(pthread_mutex_t *mutex, int *var);
void			mutextrue(pthread_mutex_t *mutex, t_bool *var);
t_bool			mutexcopyb(pthread_mutex_t *mutex, t_bool var);
int				mutexcopyi(pthread_mutex_t *mutex, int var);
void			mutexprint(t_platon *phl, const char *msg);

//errors_and_free
void			errorlog(char *error);
void			free_all(t_philo *data);

//Utilities
long long		ft_atol(const char *str);
unsigned long	get_time(void);
void			*ft_memcpy(void *dest, const void *src, size_t n);

#endif // !PHILOSOPHER_H
