/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:33 by scros             #+#    #+#             */
/*   Updated: 2021/08/01 23:31:38 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philosopher *philo, t_action action)
{
	long long	time;
	long long	diff;

	time = get_time_millis();
	diff = time - philo->program->start;
	pthread_mutex_lock(&philo->program->speek);
	if (action == TAKE_FORK)
		printf("%lld %d has taken a fork\n", diff, philo->id);
	else if (action == EAT)
		printf("%lld %d is eating\n", diff, philo->id);
	else if (action == SLEEP)
		printf("%lld %d is sleeping\n", diff, philo->id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", diff, philo->id);
	else if (action == DIE)
		printf("%lld %d died\n", diff, philo->id);
	pthread_mutex_unlock(&philo->program->speek);
}

void	*worker(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	if (philo->id % 2 == 0)
		usleep(philo->program->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, EAT);
		usleep(philo->program->time_to_sleep * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, SLEEP);
		usleep(philo->program->time_to_sleep * 1000);
		print_action(philo, THINK);
	}
}
