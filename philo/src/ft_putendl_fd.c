/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mforstho <mforstho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 14:22:59 by mforstho      #+#    #+#                 */
/*   Updated: 2022/10/18 17:52:08 by mforstho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static ssize_t	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

static size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

static ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	return (write(fd, s, len));
}

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	var;

	var = ft_putstr_fd(s, fd);
	if (var < 0)
		return (-1);
	if (ft_putchar_fd('\n', fd) < 0)
		return (-1);
	return (var + 1);
}
