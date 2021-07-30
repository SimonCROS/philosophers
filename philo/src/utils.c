/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:47:26 by scros             #+#    #+#             */
/*   Updated: 2021/07/30 23:25:31 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
