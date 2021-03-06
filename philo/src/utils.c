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

void	ft_bzero(void *s, size_t n)
{
	size_t	cur;

	while (n)
	{
		if (n >= sizeof(long))
		{
			cur = sizeof(long);
			*((long *)s) = 0;
		}
		else
		{
			cur = 1;
			*((char *)s) = 0;
		}
		s += cur;
		n -= cur;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	pointer = malloc(count * size);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, count * size);
	return (pointer);
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
