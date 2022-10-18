/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:49 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/18 17:56:17 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gettime(size_t *dst)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	*dst = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
}

void	print_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->deathcheck);
	if (philo->data->alive != true)
	{
		pthread_mutex_unlock(&philo->data->deathcheck);
		return ;
	}
	pthread_mutex_unlock(&philo->data->deathcheck);
	pthread_mutex_lock(&philo->data->printflock);
	gettime(&philo->t_print);
	printf("%zu %d %s\n", (philo->t_print - philo->data->t_start), philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->data->printflock);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

bool	is_alive(t_data *data)
{
	bool	ans;

	pthread_mutex_lock(&data->deathcheck);
	ans = data->alive;
	pthread_mutex_unlock(&data->deathcheck);
	return (ans);
}

void	usleep_death(t_philo *philo, int sleep)
{
	size_t	begin;
	size_t	current;

	gettime(&begin);
	gettime(&current);
	while (current - begin < (size_t)sleep)
	{
		if (is_alive(philo->data) != true)
			break ;
		if ((current - philo->t_meal)
			>= (size_t)philo->data->t_to_die)
		{
			print_message(philo, "died");
			pthread_mutex_lock(&philo->data->deathcheck);
			philo->data->alive = false;
			pthread_mutex_unlock(&philo->data->deathcheck);
			break ;
		}
		usleep(500);
		gettime(&current);
	}
}

void	philofunc(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	while (true)
	{
		pthread_mutex_lock(first);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(second);
		print_message(philo, "has taken a fork");
		if (is_alive(philo->data) != true)
		{
			pthread_mutex_unlock(second);
			pthread_mutex_unlock(first);
			break ;
		}
		gettime(&philo->t_meal);
		print_message(philo, "is eating");
		usleep_death(philo, philo->data->t_to_eat);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		if (is_alive(philo->data) != true)
			break ;
		philo->meals_eaten++;
		if (philo->data->t_must_eat != -1
			&& philo->meals_eaten == philo->data->t_must_eat)
		{
			print_message(philo, "finished meals");
			break ;
		}
		print_message(philo, "is sleeping");
		usleep_death(philo, philo->data->t_to_sleep);
		if (is_alive(philo->data) != true)
			break ;
		print_message(philo, "is thinking");
	}
}

void	*philo_thread(void *my_philo)
{
	t_philo	*philo;

	philo = (t_philo *)my_philo;
	if (philo->philo_nbr % 2 == 0)
		philofunc(philo, philo->fork_left, philo->fork_right);
	else
		philofunc(philo, philo->fork_right, philo->fork_left);
	return (NULL);
}

void	leakfunc(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_data			data;
	pthread_t		*thread_id;
	t_philo			*philo;
	int				i;

	// atexit(leakfunc);
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Incorrect argumentation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	gettime(&data.t_start);
	if (init_arguments(&data, argc, argv) == false)
	{
		ft_putendl_fd("Chars or negative numbers are not allowed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (data.n_philos == 1)
	{
		gettime(&data.t_current);
		printf("%zu 1 has taken a fork\n", (data.t_current - data.t_start));
		usleep(data.t_to_die * 1000);
		gettime(&data.t_current);
		printf("%zu 1 died\n", (data.t_current - data.t_start));
		return (EXIT_SUCCESS);
	}
	thread_id = malloc(sizeof(pthread_t) * data.n_philos);
	philo = malloc(sizeof(t_philo) * data.n_philos);
	if (thread_id == NULL || philo == NULL)
	{
		free(thread_id);
		free(philo);
		ft_putendl_fd("Test", STDERR_FILENO);
		return (EXIT_SUCCESS);	//hiervoor nog freeen
	}
	init_philos(&data, philo);
	init_forks(&data, philo);
	pthread_mutex_init(&data.printflock, NULL);
	pthread_mutex_init(&data.deathcheck, NULL);
	i = 0;
	while (i < data.n_philos)
	{
		if (pthread_create(&thread_id[i], NULL, philo_thread, &philo[i])
			!= SYS_OK)
		{
			data.n_philos = i;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data.n_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	free(thread_id);
	free(philo);
	pthread_mutex_destroy(&data.deathcheck);
	pthread_mutex_destroy(&data.printflock);
	destroy_forks(&data);
	return (EXIT_SUCCESS);
}
