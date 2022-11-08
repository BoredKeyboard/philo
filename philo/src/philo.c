/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:49 by mforstho      #+#    #+#                 */
/*   Updated: 2022/11/08 18:06:13 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_with_msg(char *msg, int fd, int value)
{
	ft_putendl_fd(msg, fd);
	return (value);
}

void	gettime(size_t *dst)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	*dst = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
}

void	*one_philo(t_philo *philo)
{
	gettime(&philo->data->t_current);
	pthread_mutex_lock(philo->fork_left);
	printf("%zu 1 has taken a fork\n",
		(philo->data->t_current - philo->data->t_start));
	while (true)
	{
		pthread_mutex_lock(&philo->data->deathcheck);
		if (philo->data->alive == false)
		{
			pthread_mutex_unlock(&philo->data->deathcheck);
			pthread_mutex_unlock(philo->fork_left);
			break ;
		}
		pthread_mutex_unlock(&philo->data->deathcheck);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			*philo;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Incorrect argumentation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (init_arguments(&data, argc, argv) == false)
		return (return_with_msg("Error: args", STDERR_FILENO, EXIT_FAILURE));
	philo = malloc(sizeof(t_philo) * data.n_philos);
	if (philo == NULL)
	{
		free(data.forks);
		return (return_with_msg("Error: malloc", STDERR_FILENO, EXIT_SUCCESS));
	}
	if (initialize_all(&data, philo) != true)
	{
		free(philo);
		return (EXIT_SUCCESS);
	}
	if (philos_setup(&data, philo) != true)
		return (end_all(&data, philo));
	return (end_all(&data, philo));
}
