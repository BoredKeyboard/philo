/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:26:28 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/18 17:57:52 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_start(const char *str, int *i)
{
	int	min;

	min = 1;
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '-')
	{
		min = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
	{
		min = 1;
		(*i)++;
	}
	return (min);
}

bool	ft_atoi(const char *str, int *result)
{
	int		i;
	long	converted;
	int		min;

	i = 0;
	converted = 0;
	min = parse_start(str, &i);
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i] >= '0' && str[i] <= '9')
	{
		converted = converted * 10;
		converted = converted + str[i] - '0';
		if (converted * min > INT_MAX || converted * min < INT_MIN)
			return (false);
		i++;
	}
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] != '\0')
		return (false);
	*result = converted * min;
	return (true);
}
