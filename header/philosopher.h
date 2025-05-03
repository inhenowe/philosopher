/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:30:29 by aleortiz          #+#    #+#             */
/*   Updated: 2025/04/29 12:31:10 by aleortiz         ###   ########.fr       */
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

/*-------constants Utilities-------*/
# define MA1 "Error\nPlease insert the data as follows: Philo:x Die:x Eat:x\
Sleep:x Musteat:x"

/*-------enum Utilities-------*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/*-------strcut philos-------*/
typedef struct s_platon
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*deaht;
	pthread_mutex_t	*food;
}	t_platon;

/*-------struct data argu-------*/
typedef struct s_philo
{
	int			numPhilo;
	int			timeDie_ms;
	int			timeEat_ms;
	int			timeNap_ms;
	int			MustEat;
	t_platon	*th;
}	t_philo;

/*-------funtion of src-------*/
//checkers
t_bool		argcheck(int argc, char **spl, t_philo *data);

//errors
void		errorlog(char *error);

//Utilities
long long	ft_atol(const char *str);

#endif // !PHILOSOPHER_H
