/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:18 by scros             #+#    #+#             */
/*   Updated: 2021/08/01 15:00:35 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/*** Defines ******************************************************************/

# define TRUE 1
# define FALSE 0

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
	int				stop_after;
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

int		start(t_philosophers_data *data);

/*** Utils ********************************************************************/

int		pint(char *str, int *result, int min);
ssize_t	ft_putendl_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
