/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:22:49 by aleortiz          #+#    #+#             */
/*   Updated: 2025/04/29 15:23:01 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

static int	ft_espace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

long long	ft_atol(const char *str)
{
	int			simbolo;
	int			ctu;
	long long	num;

	ctu = 0;
	simbolo = 1;
	num = 0;
	while (ft_espace(str[ctu]))
		ctu++;
	if (str[ctu] == '+' || str[ctu] == '-')
	{
		if (str[ctu] == '-')
			simbolo *= -1;
		ctu++;
	}
	while (str[ctu] >= '0' && str[ctu] <= '9')
	{
		num = num * 10 + (str[ctu] - '0');
		ctu++;
	}
	return (num * simbolo);
}
