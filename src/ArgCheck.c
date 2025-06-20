	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgCheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:43:38 by aleortiz          #+#    #+#             */
/*   Updated: 2025/04/30 10:04:39 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static t_bool	is_real_num(char **nums, t_philo *data);
static void		charge_nums(char **nums, t_philo *data);

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
		j = -1;
		while (nums[i][++j])
			if (nums[i][j] < '0' || nums[i][j] > '9')
				return (errorlog(MA2), TRUE);
	}
	charge_nums(nums, data);
	if (data->numPhilo > 200)
		return (errorlog(MA3), TRUE);
	return (FALSE);
}

static void	charge_nums(char **nums, t_philo *data)
{
	data->numPhilo = ft_atol(nums[0]);
	data->timeDie_ms = ft_atol(nums[1]);
	data->timeEat_ms =  ft_atol(nums[2]);
	data->timeNap_ms = ft_atol(nums[3]);
	if (nums[4])
		data->MustEat =  ft_atol(nums[4]);
}
