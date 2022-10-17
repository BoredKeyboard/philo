/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:35:49 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/13 16:16:35 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_arguments(t_data *data, int argc, char *argv[])
{
	if (ft_atoi(argv[1], &data->n_philos) == false
		|| ft_atoi(argv[2], &data->t_to_die) == false
		|| ft_atoi(argv[3], &data->t_to_eat) == false
		|| ft_atoi(argv[4], &data->t_to_sleep) == false)
		return (false);
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &data->t_must_eat) == false)
			return (false);
	}
	data->fork_test = true;
	data->current_philo = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
		return (false);
	return (true);
}

void	init_forks(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->n_philos)
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
		i++;
	}
}

void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].data = data;
		philo[i].philo_nbr = i + 1;
		i++;
	}
}

void	philo_even(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&philo->data->printflock);
	printf("Philo %d started eating\n", philo->philo_nbr);
	printf("Philo %d is done eating\n", philo->philo_nbr);
	pthread_mutex_unlock(&philo->data->printflock);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_uneven(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	pthread_mutex_lock(&philo->data->printflock);
	printf("Philo %d started eating\n", philo->philo_nbr);
	printf("Philo %d is done eating\n", philo->philo_nbr);
	pthread_mutex_unlock(&philo->data->printflock);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	*philo_thread(void *my_philo)
{
	t_philo	*philo;

	philo = (t_philo *)my_philo;
	if (philo->philo_nbr % 2 == 0)
		philo_even(philo);
	else
		philo_uneven(philo);
	return (NULL);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
}

void	leakfunc(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_data			data;
	pthread_t		*thread_id;
	t_philo			*philo;
	int				i;

	// atexit(leakfunc);
	if (argc < 5 || argc > 6)
	{
		printf("Incorrect argumentation\n");
		return (EXIT_FAILURE);
	}
	if (init_arguments(&data, argc, argv) == false)
		return (EXIT_FAILURE);
	thread_id = malloc(sizeof(pthread_t) * data.n_philos);
	philo = malloc(sizeof(t_philo) * data.n_philos);
	if (thread_id == NULL || philo == NULL)
		return (EXIT_SUCCESS);	//hiervoor nog freeen
	printf("Test\n");
	init_philos(&data, philo);
	printf("Test1\n");
	init_forks(&data, philo);
	pthread_mutex_init(&data.printflock, NULL);
	i = 0;
	while (i < data.n_philos)
	{
		pthread_create(&thread_id[i], NULL, philo_thread, &philo[i]);
		i++;
	}
	i = 0;
	while (i < data.n_philos)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&data.printflock);
	destroy_forks(&data);
	free(thread_id);
	free(philo);
	return (EXIT_SUCCESS);
}

/*

void	*test_thread(void *my_data)
{
	t_data	*data;

	data = (t_data *)my_data;
	pthread_mutex_lock(&data->lock);
	if (data->fork_test == true)
	{
		printf("True, setting to false\n");
		data->fork_test = false;
	}
	else
	{
		printf("False, setting to true\n");
		data->fork_test = true;
	}
	pthread_mutex_unlock(&data->lock);
	return (NULL);
}

void	free_array(void *arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

*/

/*
void	*test_thread(void *my_philo)
{
	t_philo	*philo;

	philo = (t_philo *)my_philo;
	pthread_mutex_lock(&philo->data->printflock);
	pthread_mutex_lock(philo->fork_right);
	usleep(1000);		//AAAAAAAA
	pthread_mutex_lock(philo->fork_left);

	printf("Philo %d started eating\n", philo->philo_nbr);
	printf("Philo %d is done eating\n", philo->philo_nbr);

	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(&philo->data->printflock);
	return (NULL);
}
*/