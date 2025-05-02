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
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/*-------constants Utilities-------*/
# define MA1 "Error\nPlease insert the data as follows: Philo:x Die:x Eat:x\
Sleep:x Musteat:x"

/*-------enum Utilities-------*/
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/*-------struct data argu-------*/
typedef struct s_philo
{
	int	numPhilo;
	int	timeDie_ms;
	int	timeEat_ms;
	int	timeNap_ms;
	int	MustEat;
}	t_philo;

/*-------funtion of src-------*/
//checkers
t_bool	argcheck(int argc, char **spl, t_philo *data);

//errors
void	errorlog(char *error);


#endif // !PHILOSOPHER_H
