/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:54:13 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/08 11:27:58 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	gtime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(int timeobj, t_philo *p)
{
	size_t		time;
	size_t		nb_of_philo;
	t_boolean	is_dead;

	time = gtime();
	pthread_mutex_lock(&p->data_race);
	nb_of_philo = p->nb_of_philo;
	is_dead = p->is_dead;
	pthread_mutex_unlock(&p->data_race);
	while (gtime() - time < (size_t)timeobj && is_dead == FALSE)
		usleep(nb_of_philo * 2);
}

int	all_eat(t_philo *p)
{
	int			i;
	t_boolean	is_full;

	i = 0;
	while (i < p->nb_of_philo)
	{
		pthread_mutex_lock(&p->data_race);
		is_full = p->is_full[i];
		pthread_mutex_unlock(&p->data_race);
		if (is_full == FALSE)
			return (1);
		i++;
	}
	if (p->as_eaten == -1)
		return (1);
	return (0);
}

void	ft_free(t_philo	*p)
{
	free(p->threadtab);
	p->threadtab = NULL;
	free(p->fork);
	p->fork = NULL;
	free(p->is_full);
	free(p->last_meal);
}

t_boolean	ended(t_philo *p)
{
	size_t		is_dead;
	t_boolean	meals_end;

	pthread_mutex_lock(&p->data_race);
	is_dead = p->is_dead;
	meals_end = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	if (meals_end == TRUE || is_dead == TRUE)
		return (TRUE);
	return (FALSE);
}
