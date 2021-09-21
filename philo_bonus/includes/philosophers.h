/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 22:23:18 by scros             #+#    #+#             */
/*   Updated: 2021/08/02 12:26:45 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
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
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			stop_after;
	long long	start;
	pid_t		*childs;
	sem_t		*speek;
	sem_t		*forks;
	sem_t		*meals;
	sem_t		*finish;
};

struct s_philosopher
{
	unsigned int	id;
	long long		last_meal;
	t_program_data	*data;
	sem_t			*check;
	int				eat_count;
};

enum e_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
};

void		*worker(t_philosopher philo, t_program_data *data);

/*** Utils ********************************************************************/

void		custom_usleep(long long microseconds);
int			pint(char *str, int *result, int min);
sem_t		*ft_sem_open(char *name, int size);
ssize_t		ft_putendl_fd(char *s, int fd);
long long	get_time_millis(void);

void		print_action(int id, t_program_data *data, char *message);

/*** Exit *********************************************************************/

int			show_help(void);
int			show_error(t_program_data *data);
int			quit_philo(t_program_data *data);

#endif
