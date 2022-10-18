/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:14:53 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/18 17:48:16 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define SYS_OK 0

typedef struct s_data
{
	int				n_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				t_must_eat;
	bool			fork_test;
	pthread_mutex_t	printflock;
	pthread_mutex_t	deathcheck;
	pthread_mutex_t	*forks;
	int				current_philo;
	size_t			t_start;
	size_t			t_current;
	bool			alive;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				philo_nbr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				meals_eaten;
	size_t			t_current;
	size_t			t_meal;
	size_t			t_print;
}	t_philo;

bool	ft_atoi(const char *str, int *result) \
			__attribute__((warn_unused_result));
int		ft_isdigit(int c);
int		ft_isspace(const char c);
ssize_t	ft_putendl_fd(char *s, int fd);

bool	init_arguments(t_data *data, int argc, char *argv[]);
void	init_forks(t_data *data, t_philo *philo);
void	init_philos(t_data *data, t_philo *philo);

void	gettime(size_t *dst);

#endif