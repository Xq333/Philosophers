/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phases.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:47:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/08 11:32:12 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <stddef.h>

int	ft_strncmp(const char *str1, const char *str2, size_t length)
{
	size_t	i;

	if (length == 0)
		return (0);
	if (!str1 && !str2)
		return (0);
	if (!str1)
		return ((unsigned char)str2[0]);
	if (!str2)
		return ((unsigned char)str1[0]);
	i = 0;
	while (str1[i] == str2[i] && i < length - 1 && str1[i] && str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

void	print_message(t_philo *p, t_values *v, char *message)
{
	size_t		is_dead;
	t_boolean	meals_end;

	pthread_mutex_lock(&p->data_race);
	is_dead = p->is_dead;
	meals_end = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	pthread_mutex_lock(&p->voix);
	if (is_dead == FALSE && !meals_end)
		printf("%lu %d %s\n", gtime() - p->start, v->index + 1, message);
	pthread_mutex_unlock(&p->voix);
}

void	is_eating(t_philo *p, t_values *v)
{
	pthread_mutex_lock(&p->fork[v->index]);
	print_message(p, v, MAG"has taken a fork"WHT);
	pthread_mutex_lock(&p->fork[v->prev]);
	print_message(p, v, MAG"has taken a fork"WHT);
	print_message(p, v, BLU "is eating" WHT);
	v->nb_of_meals++;
	if (v->nb_of_meals >= p->as_eaten && p->as_eaten != -1)
	{
		pthread_mutex_lock(&p->data_race);
		p->is_full[v->index] = TRUE;
		pthread_mutex_unlock(&p->data_race);
	}
	ft_sleep(p->time_to_eat, p);
	pthread_mutex_lock(&p->data_race);
	p->last_meal[v->index] = gtime() - p->start;
	pthread_mutex_unlock(&p->data_race);
	pthread_mutex_unlock(&p->fork[v->index]);
	pthread_mutex_unlock(&p->fork[v->prev]);
}

static void	multiple_philo_case(t_philo *p, t_values *v)
{
	t_boolean	ending;

	ending = FALSE;
	while (ending == FALSE)
	{
		ending = ended(p);
		is_eating(p, v);
		ending = ended(p);
		if (ending == TRUE)
			break ;
		print_message(p, v, CYN "is sleeping" WHT);
		ft_sleep(p->time_to_sleep, p);
		ending = ended(p);
		if (ending == TRUE)
			break ;
		print_message(p, v, GRN "is thinking" WHT);
		ending = ended(p);
		if (ending == TRUE)
			break ;
	}
}

void	*phases(void	*arg)
{
	t_philo		*p;
	t_values	v;
	static int	i = -1;
	int			nb;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->data_race);
	i++;
	v.index = i;
	nb = p->nb_of_philo;
	v.nb_of_meals = 0;
	v.prev = (i + 1) % p->nb_of_philo;
	pthread_mutex_unlock(&p->data_race);
	if (v.index % 2)
		usleep(100);
	if (nb == 1)
	{
		print_message(p, &v, MAG"has taken a fork"WHT);
		ft_sleep(p->time_to_die, p);
		print_message(p, &v, RED "died" WHT);
	}
	else
		multiple_philo_case(p, &v);
	return (NULL);
}
