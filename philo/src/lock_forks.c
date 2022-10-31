/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 15:03:17 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/31 15:03:46 by mforstho      ########   odam.nl         */
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
