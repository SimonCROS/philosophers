/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/07/30 23:39:37 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	show_help(void)
{
	ft_putendl_fd("\033[1;31mUsage :\n\033[1;30m./philo <nb_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [max_eat]\033[0m", 2);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_philosophers_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!(pint(argv[1], &data.nb_philos, 2)
				* pint(argv[2], &data.time_to_die, 0)
				* pint(argv[3], &data.time_to_eat, 0)
				* pint(argv[4], &data.time_to_sleep, 0)
				* (argc != 6 || pint(argv[5], &data.max_eat, 0))))
			return (show_help());
		printf("nb: %d\ndie: %d\neat: %d\nsleep: %d\nmax: %d\n",
			data.nb_philos,
			data.time_to_die,
			data.time_to_eat,
			data.time_to_sleep,
			data.max_eat);
	}
	else
		return (show_help());
	return (0);
}
