/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:52:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/09 20:33:04 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

void	*death_check(t_philo *p)
{
	size_t	start;
	size_t	last_meal;
	int		index;

	while (1)
	{
		sem_wait(p->data_race);
		start = p->start;
		last_meal = p->last_meal.tv_sec * 1000 + p->last_meal.tv_usec / 1000;
		index = p->index;
		sem_post(p->data_race);
		if (gtime() - last_meal >= (size_t)p->time_to_die)
		{
			sem_wait(p->voix);
			usleep(20);
			printf(RED "%lu %d died\n", gtime() - start, index + 1);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}
