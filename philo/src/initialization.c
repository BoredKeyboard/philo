/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialization.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 13:48:02 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/20 16:01:36 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_arguments(t_data *data, int argc, char *argv[])
{
	gettime(&data->t_start);
	if (ft_atoi(argv[1], &data->n_philos) == false
		|| ft_atoi(argv[2], &data->t_to_die) == false
		|| data->t_to_die < 0
		|| ft_atoi(argv[3], &data->t_to_eat) == false
		|| data->t_to_eat < 0
		|| ft_atoi(argv[4], &data->t_to_sleep) == false
		|| data->t_to_sleep < 0)
		return (false);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &data->t_must_eat) == false
			|| data->t_must_eat < 0)
			return (false);
	}
	else
		data->t_must_eat = -1;
	data->current_philo = 0;
	data->alive = true;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
		return (false);
	return (true);
}

void	set_fork(t_data *data, t_philo *philo, int i)
{
	if ((i + 1) == data->n_philos)
	{
		philo[i].fork_left = &data->forks[i];
		philo[i].fork_right = &data->forks[0];
	}
	else
	{
		philo[i].fork_left = &data->forks[i];
		philo[i].fork_right = &data->forks[i + 1];
	}
}

bool	init_forks(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_forks(data, i);
			return (false);
		}
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		set_fork(data, philo, i);
		i++;
	}
	return (true);
}

void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].data = data;
		philo[i].philo_nbr = i + 1;
		philo[i].meals_eaten = 0;
		gettime(&philo[i].t_meal);
		i++;
	}
}

bool	initialize_all(t_data *data, t_philo *philo)
{
	init_philos(data, philo);
	if (init_forks(data, philo) != true)
		return (false);
	if (pthread_mutex_init(&data->printflock, NULL) != SYS_OK)
		return (false);
	if (pthread_mutex_init(&data->deathcheck, NULL) != SYS_OK)
		return (false);
	return (true);
}
