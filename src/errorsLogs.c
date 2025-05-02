/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsLogs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:55:22 by aleortiz          #+#    #+#             */
/*   Updated: 2025/04/29 13:55:24 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher.h"

void	errorlog(char *error)
{
	int	i;

	i = 0;
	while (error[i])
		write(2, &error[i++], 1);
	write(2, "\n", 1);
}
