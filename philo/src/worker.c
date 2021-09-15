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

#include "philosophers.h"

void	print_action(t_philosopher *this, char *message)
{
	long long	diff;

	diff = this->program->current - this->program->start;
	printf("%lld %d %s\n", diff, this->id, message);
}

static int	action(t_philosopher *this, t_action action)
{
	pthread_mutex_lock(&this->program->speek);
	if (this->program->stop)
	{
		pthread_mutex_unlock(&this->program->speek);
		return (FALSE);
	}
	if (action == TAKE_FORK)
		print_action(this, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(this, "is sleeping");
		this->eat_count++;
	}	
	else if (action == THINK)
		print_action(this, "is thinking");
	else if (action == EAT)
	{
		print_action(this, "is eating");
		this->last_meal = this->program->current;
	}
	pthread_mutex_unlock(&this->program->speek);
	return (TRUE);
}

void	custom_usleep(long long microseconds)
{
	long long	i;
	long long	start;

	i = 0;
	start = get_time_millis();
	while (get_time_millis() - start < microseconds / 1000)
		usleep(100);
}

void	*worker(void *data)
{
	t_philosopher	*philo;
	int				stop;

	stop = 0;
	philo = (t_philosopher *)data;
	if (philo->id % 2 == 0)
		custom_usleep(philo->program->time_to_eat * 1000);
	while (!stop)
	{
		pthread_mutex_lock(philo->left_fork);
		stop = !action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		stop = !action(philo, TAKE_FORK);
		stop = !action(philo, EAT);
		custom_usleep(philo->program->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		stop = !action(philo, SLEEP);
		custom_usleep(philo->program->time_to_sleep * 1000);
		stop = !action(philo, THINK);
	}
	return (NULL);
}
