/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:18 by scros             #+#    #+#             */
/*   Updated: 2021/07/30 23:46:11 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/*** Types ********************************************************************/

typedef struct s_philosophers_data	t_philosophers_data;

typedef struct s_philosopher		t_philosopher;

/*** Core *********************************************************************/

struct s_philosophers_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	speek;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
};

struct s_philosopher
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_eat;
	int				eat_count;
};

/*** Utils ********************************************************************/

int			pint(char *str, int *result, int min);
ssize_t		ft_putendl_fd(char *s, int fd);

#endif
