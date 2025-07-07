/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:22:49 by aleortiz          #+#    #+#             */
/*   Updated: 2025/07/03 11:52:30 by aleortiz         ###   ########.fr       */
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

unsigned long	get_time(void)
{
	struct timeval			tv;
	unsigned long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	unsigned const char	*c_src;
	size_t				ctu_d;

	c_dest = dest;
	c_src = src;
	ctu_d = 0;
	if (!dest && !src && n > 0)
		return ((void *) 0);
	while (ctu_d < n)
	{
		c_dest[ctu_d] = c_src[ctu_d];
		ctu_d++;
	}
	if (ctu_d < n)
		c_dest[ctu_d] = '\0';
	return (dest);
}