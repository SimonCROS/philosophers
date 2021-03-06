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

static void	init_philosophers(t_program_data *data)
{
	int				i;
	t_philosopher	*philosopher;

	i = 0;
	while (i < data->nb_philos)
	{
		philosopher = &data->philosophers[i];
		philosopher->id = i + 1;
		philosopher->program = data;
		philosopher->last_meal = data->start;
		philosopher->left_fork = &data->forks[i];
		i++;
		philosopher->right_fork = &data->forks[i % data->nb_philos];
	}
}

static int	check_stop(t_program_data *data)
{
	int				i;
	int				finished;
	long long		current;
	t_philosopher	*philosopher;

	i = 0;
	finished = data->stop_after != -1;
	current = get_time_millis();
	while (i < data->nb_philos && !data->stop)
	{
		philosopher = &data->philosophers[i];
		if (philosopher->eat_count < data->stop_after)
			finished = 0;
		if (current - philosopher->last_meal > data->time_to_die)
		{
			data->stop = TRUE;
			print_action(philosopher, "died");
			return (TRUE);
		}
		i++;
	}
	if (finished)
		return (TRUE);
	return (FALSE);
}

static void	wait_end(t_program_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->speak);
		if (check_stop(data))
		{
			data->stop = TRUE;
			break ;
		}
		pthread_mutex_unlock(&data->speak);
	}
}

static int	start(t_program_data *data)
{
	int				i;
	t_philosopher	*philosopher;

	data->stop = FALSE;
	data->start = get_time_millis();
	init_philosophers(data);
	i = 0;
	while (i < data->nb_philos)
	{
		philosopher = &data->philosophers[i];
		if (pthread_create(&philosopher->thread, NULL, worker, philosopher))
		{
			pthread_mutex_lock(&data->speak);
			data->stop = TRUE;
			pthread_mutex_unlock(&data->speak);
			return (FALSE);
		}
		else
			pthread_detach(philosopher->thread);
		i++;
	}
	wait_end(data);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_program_data	data;
	int				i;

	if (argc != 5 && argc != 6)
		return (show_help());
	data.stop_after = -1;
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
	pthread_mutex_init(&data.speak, NULL);
	i = 0;
	while (i < data.nb_philos)
		pthread_mutex_init(&data.forks[i++], NULL);
	if (!start(&data))
		return (show_error(&data, TRUE));
	return (quit_philo(&data, TRUE));
}
