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

#include <signal.h>

#include "philosophers.h"

static void	*meal_monitor(void *arg)
{
	t_program_data	*data;
	int				i;

	data = (t_program_data *)arg;
	i = data->nb_philos;
	while (i--)
		sem_wait(data->meals);
	sem_post(data->finish);
	return (NULL);
}

static void	wait_end(t_program_data *data)
{
	int			i;
	pthread_t	thread;

	pthread_create(&thread, NULL, meal_monitor, data);
	sem_wait(data->finish);
	i = data->nb_philos;
	while (i--)
		kill(data->childs[i], SIGKILL);
}

static void	start(t_program_data *data)
{
	int	i;
	int	child;

	data->start = get_time_millis();
	i = 0;
	while (i < data->nb_philos)
	{
		child = fork();
		if (child == -1)
			quit_philo(data);
		else if (child == 0)
			worker((t_philosopher){i + 1, data->start, data, NULL, 0}, data);
		data->childs[i] = child;
		i++;
	}
	wait_end(data);
}

int	main(int argc, char *argv[])
{
	t_program_data	data;

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
	data.childs = malloc(sizeof(pid_t) * data.nb_philos);
	data.forks = ft_sem_open("forks", data.nb_philos);
	data.speek = ft_sem_open("speek", 1);
	data.meals = ft_sem_open("meals", 0);
	data.finish = ft_sem_open("finish", 0);
	if (data.forks == SEM_FAILED || data.speek == SEM_FAILED
		|| data.meals == SEM_FAILED || data.finish == SEM_FAILED)
		return (show_error(&data));
	start(&data);
	return (quit_philo(&data));
}
