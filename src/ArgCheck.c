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

	return (FALSE);
}

static t_bool	is_real_num(char **nums, t_philo *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (nums[++i])
		while (nums[i][++j])
			if (nums[i][j] < '0' && nums[i][++j] > '9')
				return (TRUE);
	charge_nums(nums, data);
}

static void		charge_nums(char **nums, t_philo *data)
{
 
}
