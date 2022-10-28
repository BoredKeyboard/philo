/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   one_philo.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 15:49:33 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/27 15:53:00 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_data *data)
{
	gettime(&data->t_current);
	printf("%zu 1 has taken a fork\n", (data->t_current - data->t_start));
	usleep(data->t_to_die * 1000);
	gettime(&data->t_current);
	printf("%zu 1 died\n", (data->t_current - data->t_start));
	return (NULL);
}
