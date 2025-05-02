/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleortiz <aleortiz@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:30:47 by aleortiz          #+#    #+#             */
/*   Updated: 2025/04/29 12:31:10 by aleortiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../header/philosopher.h"

void	initdata(t_philo *data);

int main(int argc, char *argv[])
{
	t_philo	data;

	initdata(&data);
	if (argcheck(argc - 1, argv + 1, &data))
		exit(1);
}

void	initdata(t_philo *data)
{
	data->numPhilo = 0;
	data->timeDie_ms = 0;
	data->timeEat_ms = 0;
	data->timeNap_ms = 0;
	data->MustEat = 0;
}
