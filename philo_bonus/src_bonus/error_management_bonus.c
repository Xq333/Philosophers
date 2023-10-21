/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:35:28 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/05/12 15:25:21 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

static int	verif2(const char *str)
{
	if (!str[1] && (str[0] == '-' || str[0] == '+'))
		return (1);
	return (0);
}

static int	verif(const char *str)
{
	int	i;

	i = -1;
	if (str[i + 1] && (str[i + 1] == '-' || str[i + 1] == '+'))
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
	}
	if (verif2(str))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	i;
	long	y;
	long	rep;

	i = 0;
	y = 1;
	rep = 0;
	if (verif(str))
		return (-2147483649);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			y = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		rep = rep * 10 + (str[i++] - 48);
	if ((rep * y) > 2147483647 || (rep * y) < 1)
		return (-2147483649);
	return (rep * y);
}

static int	error_printer(int error)
{
	if (error == 1)
		printf(RED"Not enough arguments");
	if (error == 2)
		printf(RED"Too many arguments");
	if (error == 3)
		printf(RED"Arguments must be not-null/positives integers");
	return (1);
}

int	error_gestion(int ac, char **av)
{
	int	i;
	int	error;

	error = 0;
	if (ac < 5)
		return (error_printer(error = 1));
	if (ac > 6)
		return (error_printer(error = 2));
	i = 0;
	while (av[++i])
		if (ft_atol(av[i]) == -2147483649)
			return (error_printer(error = 3));
	return (0);
}
