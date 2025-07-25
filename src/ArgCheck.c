/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgCheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:43:38 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/02 15:56:09 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static t_bool	is_real_num(char **nums, t_philo *data);
static void		charge_nums(char **nums, t_philo *data);
static int		ft_strlen(char *str);

t_bool	argcheck(int argc, char **spl, t_philo *data)
{
	if (argc < 4 || argc > 5)
		return (errorlog(MA1), TRUE);
	if (is_real_num(spl, data))
		return (TRUE);
	return (FALSE);
}

static t_bool	is_real_num(char **nums, t_philo *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (nums[++i])
	{
		if (ft_strlen(nums[i]) == 0)
			return (errorlog(MA2), TRUE);
		if (ft_strlen(nums[i]) > 10)
			return (errorlog("Error\nNumber too big"), TRUE);
		j = -1;
		while (nums[i][++j])
		{
			if (nums[i][j] < '0' || nums[i][j] > '9')
				return (errorlog(MA2), TRUE);
		}
	}
	charge_nums(nums, data);
	if (data->num_philo > 200)
		return (errorlog(MA3), TRUE);
	if (data->num_philo == 0)
		return (errorlog(MA3), TRUE);
	return (FALSE);
}

static void	charge_nums(char **nums, t_philo *data)
{
	data->num_philo = ft_atol(nums[0]);
	data->time_die_ms = ft_atol(nums[1]);
	data->time_eat_ms = ft_atol(nums[2]);
	data->time_nap_ms = ft_atol(nums[3]);
	if (nums[4])
		data->must_eat = ft_atol(nums[4]);
}

static int	ft_strlen(char *str)
{
	int	ctu_str;

	ctu_str = 0;
	while (str[ctu_str] != 0)
		ctu_str++;
	return (ctu_str);
}
