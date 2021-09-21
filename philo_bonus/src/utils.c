/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:47:26 by scros             #+#    #+#             */
/*   Updated: 2021/08/01 23:06:46 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
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

sem_t	*ft_sem_open(char *name, int size)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, size);
	sem_unlink(name);
	return (sem);
}

int	pint(char *str, int *result, int min)
{
	int	ret;
	int	mul;

	ret = 0;
	mul = 1;
	if (*str == '-')
	{
		str++;
		if (!(*str))
			return (0);
		mul = -1;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*str - '0') * mul;
		if ((ret < 0 && mul == 1) || (ret > 0 && mul == -1))
			return (0);
		str++;
	}
	if (ret < min)
		return (0);
	*result = ret;
	return (!(*str));
}

ssize_t	ft_putendl_fd(char *s, int fd)
{
	int	len;

	if (s)
	{
		len = 0;
		while (s[len])
			len++;
		return (write(fd, s, len) + write(fd, "\n", 1));
	}
	return (write(fd, "\n", 1));
}
