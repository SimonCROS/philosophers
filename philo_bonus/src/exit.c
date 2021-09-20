/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/08/02 12:32:42 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philo(t_program_data *data)
{
	sem_unlink("speek");
	sem_unlink("forks");
	free(data->philosophers);
}

int	show_help(void)
{
	ft_putendl_fd("\033[1;31mUsage :\n\033[1;30m./philo <nb_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [stop_after_eat]\033[0m", 2);
	return (EXIT_FAILURE);
}

int	show_error(t_program_data *data)
{
	free_philo(data);
	ft_putendl_fd("\033[31mAn internal error occurred.\033[0m", 2);
	return (EXIT_FAILURE);
}

int	quit_philo(t_program_data *data)
{
	free_philo(data);
	return (EXIT_SUCCESS);
}
