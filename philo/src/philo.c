/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:49 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/26 15:03:22 by mforstho      ########   odam.nl         */
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
	if (data.n_philos == 1)
		return (one_philo(&data));
	philo = malloc(sizeof(t_philo) * data.n_philos);
	if (philo == NULL)
	{
		free(philo);
		free(data.forks);
		return (return_with_msg("Error: malloc", STDERR_FILENO, EXIT_SUCCESS));
	}
	if (initialize_all(&data, philo) != true
		|| philos_setup(&data, philo) != true)
		return (end_all(&data, philo));
	return (end_all(&data, philo));
}
