/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generic.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:47:19 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/20 13:42:28 by mforstho      ########   odam.nl         */
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

void	gettime(size_t *dst)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	*dst = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
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
		if ((current - philo->t_meal)
			>= (size_t)philo->data->t_to_die)
		{
			philo->data->alive = false;
			pthread_mutex_unlock(&philo->data->deathcheck);
			print_message_unchecked(philo, "died");
			break ;
		}
		pthread_mutex_unlock(&philo->data->deathcheck);
		usleep(500);
		gettime(&current);
	}
}