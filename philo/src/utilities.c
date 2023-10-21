/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:34:58 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/06 18:35:29 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	wait_pthreads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		pthread_join(p->threadtab[i++], NULL);
	return ;
}

int	create_mutextab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		if (pthread_mutex_init(&p->fork[i++], NULL) != 0)
			return (1);
	}
	return (0);
}

void	destroy_mutextab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		pthread_mutex_destroy(&p->fork[i++]);
}

static void	initialize_status(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		p->is_full[i] = FALSE;
		p->last_meal[i] = 0;
		i++;
	}
}

t_philo	initializer(char **av)
{
	t_philo	p;

	p.nb_of_philo = ft_atol(av[1]);
	p.is_dead = FALSE;
	p.threadtab = malloc(sizeof(pthread_t) * ft_atol(av[1]));
	p.fork = malloc(sizeof(pthread_mutex_t) * p.nb_of_philo);
	p.is_full = malloc(sizeof(t_boolean) * p.nb_of_philo);
	p.last_meal = malloc(sizeof(size_t) * p.nb_of_philo);
	p.time_to_die = ft_atol(av[2]);
	p.time_to_eat = ft_atol(av[3]);
	p.time_to_sleep = ft_atol(av[4]);
	p.meals_end = FALSE;
	p.start = gtime();
	p.as_eaten = -1;
	initialize_status(&p);
	if (av[5])
		p.as_eaten = ft_atol(av[5]);
	return (p);
}
