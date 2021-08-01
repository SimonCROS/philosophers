/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/08/01 16:10:09 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	quit_philo(t_philosophers_data *data, int destroy_mutex)
{
	int	i;

	if (destroy_mutex)
	{
		i = 0;
		pthread_mutex_destroy(&data->speek);
		while (i < data->nb_philos)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	free(data->forks);
	data->forks = NULL;
	free(data->philosophers);
	data->philosophers = NULL;
	return (EXIT_SUCCESS);
}

static int	show_help(void)
{
	ft_putendl_fd("\033[1;31mUsage :\n\033[1;30m./philo <nb_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [stop_after_eat]\033[0m", 2);
	return (EXIT_FAILURE);
}

static int	show_error(t_philosophers_data *data, int destroy_mutex)
{
	quit_philo(data, destroy_mutex);
	ft_putendl_fd("\033[31mAn internal error occurred.\033[0m", 2);
	return (EXIT_FAILURE);
}

static void	init_philosophers(t_philosophers_data *data)
{
	int				i;
	t_philosopher	*philosopher;

	i = 0;
	while (i < data->nb_philos)
	{
		philosopher = &data->philosophers[i];
		philosopher->left_fork = &data->forks[i];
		i++;
		philosopher->right_fork = &data->forks[i % data->nb_philos];
	}
}

int	start(t_philosophers_data *data)
{
	init_philosophers(data);
	for (int i = 0; i < data->nb_philos; i++)
	{
		printf("%p -> %p = ", data->philosophers[i].left_fork, data->philosophers[i].right_fork);
	}
	printf("%p\n", data->philosophers[0].left_fork);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_philosophers_data	data;
	int					i;

	if (argc != 5 && argc != 6)
		return (show_help());
	if (!(pint(argv[1], &data.nb_philos, 0)
			* pint(argv[2], &data.time_to_die, 0)
			* pint(argv[3], &data.time_to_eat, 0)
			* pint(argv[4], &data.time_to_sleep, 0)
			* (argc != 6 || pint(argv[5], &data.stop_after, 0))))
		return (show_help());
	if (data.nb_philos == 0)
		return (EXIT_SUCCESS);
	data.forks = ft_calloc(data.nb_philos, sizeof(pthread_mutex_t));
	data.philosophers = ft_calloc(data.nb_philos, sizeof(t_philosopher));
	if (!data.forks || !data.philosophers)
		return (show_error(&data, FALSE));
	pthread_mutex_init(&data.speek, NULL);
	i = 0;
	while (i < data.nb_philos)
		pthread_mutex_init(&data.forks[i++], NULL);
	if (!start(&data))
		return (show_error(&data, TRUE));
	return (quit_philo(&data, TRUE));
}
