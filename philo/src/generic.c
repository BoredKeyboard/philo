/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generic.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:47:19 by mforstho      #+#    #+#                 */
/*   Updated: 2022/11/08 18:06:23 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_data *data, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
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
		pthread_mutex_lock(&philo->data->deathcheck);
		if (philo->data->alive != true)
		{
			pthread_mutex_unlock(&philo->data->deathcheck);
			break ;
		}
		pthread_mutex_unlock(&philo->data->deathcheck);
		usleep(500);
		gettime(&current);
	}
}

int	end_all(t_data *data, t_philo *philo)
{
	free(philo);
	pthread_mutex_destroy(&data->deathcheck);
	pthread_mutex_destroy(&data->printflock);
	pthread_mutex_destroy(&data->meal_lock);
	destroy_forks(data, data->n_philos);
	return (EXIT_SUCCESS);
}
