/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/08/02 12:26:50 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "philosophers.h"

void	print_action(int id, t_program_data *data, char *message)
{
	long long	diff;

	diff = get_time_millis() - data->start;
	printf("%lld %d %s\n", diff, id, message);
}

static void	action(t_philosopher *this, t_program_data *data, t_action action)
{
	sem_wait(this->check);
	sem_wait(data->speak);
	if (!this->died)
	{
		if (action == TAKE_FORK)
			print_action(this->id, data, "has taken a fork");
		else if (action == SLEEP)
		{
			print_action(this->id, data, "is sleeping");
			this->eat_count++;
			if (this->eat_count == data->stop_after)
				sem_post(data->meals);
		}	
		else if (action == THINK)
			print_action(this->id, data, "is thinking");
		else if (action == EAT)
		{
			print_action(this->id, data, "is eating");
			this->last_meal = get_time_millis();
		}
	}
	sem_post(data->speak);
	sem_post(this->check);
}

static void	make_semid(unsigned int id, char result[9])
{
	int	i;
	int	num;

	i = 8;
	result[i] = '\0';
	while (i--)
	{
		num = id % 16;
		if (num < 10)
			result[i] = '0' + num;
		else
			result[i] = 'A' + (num - 10);
		id /= 16;
	}
}

void	*monitor(void *arg)
{
	t_philosopher	*philo;
	t_program_data	*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(philo->check);
		if (get_time_millis() - philo->last_meal > data->time_to_die)
		{
			sem_wait(data->speak);
			philo->died = 1;
			print_action(philo->id, data, "died");
			sem_post(data->speak);
			sem_post(philo->check);
			sem_post(data->finish);
			break ;
		}
		sem_post(philo->check);
	}
	return (NULL);
}

void	*worker(t_philosopher philo, t_program_data *data)
{
	char		semid[9];
	pthread_t	thread;

	make_semid(philo.id, semid);
	philo.check = sem_open(semid, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(semid);
	pthread_create(&thread, NULL, monitor, &philo);
	if (philo.id % 2 == 0)
		custom_usleep(data->time_to_eat * 1000);
	while (1)
	{
		sem_wait(data->forks);
		action(&philo, data, TAKE_FORK);
		sem_wait(data->forks);
		action(&philo, data, TAKE_FORK);
		action(&philo, data, EAT);
		custom_usleep(data->time_to_eat * 1000);
		sem_post(data->forks);
		sem_post(data->forks);
		action(&philo, data, SLEEP);
		custom_usleep(data->time_to_sleep * 1000);
		action(&philo, data, THINK);
	}
	exit(EXIT_SUCCESS);
}
