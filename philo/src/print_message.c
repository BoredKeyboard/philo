/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:33:36 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/31 14:33:26 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->printflock);
	pthread_mutex_lock(&philo->data->deathcheck);
	if (philo->data->alive != true)
	{
		pthread_mutex_unlock(&philo->data->deathcheck);
		pthread_mutex_unlock(&philo->data->printflock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->deathcheck);
	gettime(&philo->t_print);
	printf("%zu %d %s\n", (philo->t_print - philo->data->t_start),
		philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->data->printflock);
}

void	print_message_unchecked(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->data->printflock);
	gettime(&philo->t_print);
	printf("%zu %d %s\n", (philo->t_print - philo->data->t_start),
		philo->philo_nbr, msg);
	pthread_mutex_unlock(&philo->data->printflock);
}

void	print_msg_sleep(t_philo *philo, char *msg, int sleep)
{
	print_message(philo, msg);
	usleep_death(philo, sleep);
}
