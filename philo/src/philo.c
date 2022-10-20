/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:49 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/20 15:58:49 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_with_msg(char *msg, int fd, int value)
{
	ft_putendl_fd(msg, fd);
	return (value);
}

int	one_philo(t_data *data)
{
	gettime(&data->t_current);
	printf("%zu 1 has taken a fork\n", (data->t_current - data->t_start));
	usleep(data->t_to_die * 1000);
	gettime(&data->t_current);
	printf("%zu 1 died\n", (data->t_current - data->t_start));
	return (EXIT_SUCCESS);
}

int	end_all(t_data *data, pthread_t *thread_id, t_philo *philo)
{
	free(thread_id);
	free(philo);
	pthread_mutex_destroy(&data->deathcheck);
	pthread_mutex_destroy(&data->printflock);
	destroy_forks(data, data->n_philos);
	return (EXIT_SUCCESS);
}

bool	create_philos(t_data *data, pthread_t *thread_id, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = false;
	while (i < data->n_philos)
	{
		if (pthread_create(&thread_id[i], NULL, philo_thread, &philo[i])
			!= SYS_OK)
		{
			data->n_philos = i;
			data->alive = false;
			return (false);
		}
		i++;
	}
	data->start = true;
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	pthread_t		*thread_id;
	t_philo			*philo;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Incorrect argumentation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (init_arguments(&data, argc, argv) == false)
		return (return_with_msg("Error: args", STDERR_FILENO, EXIT_FAILURE));
	if (data.n_philos == 1)
		return (one_philo(&data));
	thread_id = malloc(sizeof(pthread_t) * data.n_philos);
	philo = malloc(sizeof(t_philo) * data.n_philos);
	if (thread_id == NULL || philo == NULL)
	{
		free(thread_id);
		free(philo);
		return (return_with_msg("Error: malloc", STDERR_FILENO, EXIT_SUCCESS));
	}
	if (initialize_all(&data, philo) != true
		|| create_philos(&data, thread_id, philo) != true)
		return (end_all(&data, thread_id, philo));
	return (end_all(&data, thread_id, philo));
}
