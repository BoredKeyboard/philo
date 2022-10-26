/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:14:53 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/26 15:03:42 by mforstho      ########   odam.nl         */
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
	int				meals;
	pthread_mutex_t	printflock;
	pthread_mutex_t	deathcheck;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	int				current_philo;
	size_t			t_start;
	size_t			t_current;
	int				philos_done;
	bool			alive;
	bool			start;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		id;
	int				philo_nbr;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				eaten;
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
bool	init_forks(t_data *data, t_philo *philo);
void	init_philos(t_data *data, t_philo *philo);
bool	initialize_all(t_data *data, t_philo *philo);

void	destroy_forks(t_data *data, int amount);
void	gettime(size_t *dst);
bool	is_alive(t_data *data);
void	usleep_death(t_philo *philo, int sleep);
int		end_all(t_data *data, t_philo *philo);

void	print_message(t_philo *philo, const char *msg);
void	print_message_unchecked(t_philo *philo, const char *msg);

void	*philo_thread(void *my_philo);

void	gettime(size_t *dst);

bool	philos_setup(t_data *data, t_philo *philo);

#endif