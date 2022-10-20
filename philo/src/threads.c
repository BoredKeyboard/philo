/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 12:41:25 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/20 15:49:23 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo, pthread_mutex_t *one, pthread_mutex_t *two)
{
	pthread_mutex_lock(one);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(two);
	print_message(philo, "has taken a fork");
}

void	unlock_forks(pthread_mutex_t *one, pthread_mutex_t *two)
{
	pthread_mutex_unlock(two);
	pthread_mutex_unlock(one);
}

void	print_msg_sleep(t_philo *philo, char *msg, int sleep)
{
	print_message(philo, msg);
	usleep_death(philo, sleep);
}

void	philofunc(t_philo *philo, pthread_mutex_t *one, pthread_mutex_t *two)
{
	while (true)
	{
		lock_forks(philo, one, two);
		if (is_alive(philo->data) != true)
		{
			unlock_forks(one, two);
			break ;
		}
		gettime(&philo->t_meal);
		print_msg_sleep(philo, "is eating", philo->data->t_to_eat);
		unlock_forks(one, two);
		if (is_alive(philo->data) != true)
			break ;
		philo->meals_eaten++;
		if (philo->data->t_must_eat != -1
			&& philo->meals_eaten == philo->data->t_must_eat)
			break ;
		print_msg_sleep(philo, "is sleeping", philo->data->t_to_sleep);
		if (is_alive(philo->data) != true)
			break ;
		print_message(philo, "is thinking");
	}
}

void	*philo_thread(void *my_philo)
{
	t_philo	*philo;

	philo = (t_philo *)my_philo;
	while (true)
	{
		pthread_mutex_lock(&philo->data->deathcheck);
		if (philo->data->alive == false)
		{
			pthread_mutex_unlock(&philo->data->deathcheck);
			return (NULL);
		}
		if (philo->data->start == true)
		{
			pthread_mutex_unlock(&philo->data->deathcheck);
			break ;
		}
		pthread_mutex_unlock(&philo->data->deathcheck);
	}
	if (philo->philo_nbr % 2 == 0)
		philofunc(philo, philo->fork_left, philo->fork_right);
	else
		philofunc(philo, philo->fork_right, philo->fork_left);
	return (NULL);
}
