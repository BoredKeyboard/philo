/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:33:36 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/28 17:38:50 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->deathcheck);
	pthread_mutex_lock(&philo->data->printflock);
	if (philo->data->alive != true)
	{
		pthread_mutex_unlock(&philo->data->printflock);
		pthread_mutex_unlock(&philo->data->deathcheck);
		return (false);
	}
	philo->t_print = gettime2();
	printf("%zu %d %s\n", (philo->t_print - philo->data->t_start),
		philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->data->printflock);
	pthread_mutex_unlock(&philo->data->deathcheck);
	return (true);
}

void	print_message_unchecked(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->printflock);
	philo->t_print = gettime2();
	printf("%zu %d %s\n", (philo->t_print - philo->data->t_start),
		philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->data->printflock);
}

bool	print_msg_sleep(t_philo *philo, char *msg, int sleep)
{
	if (print_message(philo, msg) == false)
		return (false);
	if (usleep_death(philo, sleep) == false)
		return (false);
	return (true);
}
