/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:02:37 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/26 15:09:40 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death_state(t_data *data, t_philo *philo)
{
	int		i;
	size_t	current;

	i = 0;
	while (i < data->n_philos)
	{
		gettime(&current);
		pthread_mutex_lock(&data->deathcheck);
		if ((current - philo[i].t_meal) >= (size_t)philo->data->t_to_die)
		{
			philo->data->alive = false;
			pthread_mutex_unlock(&data->deathcheck);
			print_message_unchecked(&philo[i], "died");
			return (false);
		}
		pthread_mutex_unlock(&data->deathcheck);
		i++;
	}
	return (true);
}

void	check_state(t_data *data, t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos_done == data->n_philos)
		{
			pthread_mutex_unlock(&data->meal_lock);
			pthread_mutex_lock(&data->deathcheck);
			data->alive = false;
			pthread_mutex_unlock(&data->deathcheck);
			return ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		if (check_death_state(data, philo) == false)
			return ;
	}
	return ;
}

bool	create_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->start = false;
	while (i < data->n_philos)
	{
		if (pthread_create(&philo[i].id, NULL, philo_thread, &philo[i])
			!= SYS_OK)
		{
			data->n_philos = i;
			pthread_mutex_lock(&data->deathcheck);
			data->alive = false;
			pthread_mutex_unlock(&data->deathcheck);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	philos_setup(t_data *data, t_philo *philo)
{
	int	i;

	if (create_philos(data, philo) == false)
		return (false);
	gettime(&data->t_start);
	i = 0;
	while (i < data->n_philos)
	{
		philo[i].t_meal = data->t_start;
		i++;
	}
	pthread_mutex_lock(&data->deathcheck);
	data->start = true;
	pthread_mutex_unlock(&data->deathcheck);
	check_state(data, philo);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(philo[i].id, NULL);
		i++;
	}
	return (true);
}
