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

static int	print_action(t_philosopher *philo, t_action action)
{
	long long	diff;

	pthread_mutex_lock(&philo->program->speek);
	diff = philo->program->current - philo->program->start;
	if (philo->program->stop)
	{
		pthread_mutex_unlock(&philo->program->speek);
		return (FALSE);
	}
	if (action == TAKE_FORK)
		printf("%lld %d has taken a fork\n", diff, philo->id);
	else if (action == EAT)
	{
		philo->last_meal = philo->program->current;
		printf("%lld %d is eating\n", diff, philo->id);
	}
	else if (action == SLEEP)
	{
		printf("%lld %d is sleeping\n", diff, philo->id);
	}
	else if (action == THINK)
		printf("%lld %d is thinking\n", diff, philo->id);
	pthread_mutex_unlock(&philo->program->speek);
	return (TRUE);
}

void	*worker(void *data)
{
	t_philosopher	*philo;
	int				stop;

	stop = 0;
	philo = (t_philosopher *)data;
	if (philo->id % 2 == 0)
		while ( philo->program->time_to_eat * 1000)
			;
	while (!stop)
	{
		pthread_mutex_lock(philo->left_fork);
		stop = !print_action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		stop = !print_action(philo, TAKE_FORK);
		stop = !print_action(philo, EAT);
		usleep(philo->program->time_to_sleep * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		stop = !print_action(philo, SLEEP);
		usleep(philo->program->time_to_sleep * 1000);
		stop = !print_action(philo, THINK);
	}
	return (NULL);
}
