/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:18 by scros             #+#    #+#             */
/*   Updated: 2021/08/01 23:04:09 by scros            ###   ########lyon.fr   */
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

typedef struct s_program_data	t_program_data;
typedef struct s_philosopher	t_philosopher;
typedef enum e_action			t_action;

/*** Core *********************************************************************/

struct s_program_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				stop_after;
	int				died;
	long long		start;
	pthread_mutex_t	speek;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
};

struct s_philosopher
{
	int				id;
	t_program_data	*program;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal;
	int				eat_count;
	pthread_t		thread;
};

enum e_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE,
};

int			start(t_program_data *data);
void		*worker(void *philo);

/*** Utils ********************************************************************/

int			pint(char *str, int *result, int min);
ssize_t		ft_putendl_fd(char *s, int fd);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
long long	get_time_millis(void);

#endif
