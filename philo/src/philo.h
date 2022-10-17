/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:14:53 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/12 17:03:54 by mforstho      ########   odam.nl         */
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

typedef struct s_data
{
	int				n_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				t_must_eat;
	bool			fork_test;
	pthread_mutex_t	printflock;
	pthread_mutex_t	*forks;
	int				current_philo;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				philo_nbr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

int		ft_isdigit(int c);
int		ft_isspace(const char c);

bool	ft_atoi(const char *str, int *result) \
			__attribute__((warn_unused_result));

#endif