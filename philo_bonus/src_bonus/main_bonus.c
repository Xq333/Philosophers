/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:21:45 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/12 13:09:17 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/philosophers_bonus.h"

void	*eat(t_philo *p)
{
	int	i;

	i = 0;
	while (i++ < p->nb_of_philo)
		sem_wait(p->miam);
	p->meals_end = TRUE;
	sem_wait(p->voix);
	i = -1;
	while (++i < p->nb_of_philo)
		kill(p->philo_tab[i], SIGTERM);
	return (NULL);
}

int	forktab(t_philo *p)
{
	int			i;

	i = -1;
	if (p->as_eaten)
		while (++i < p->nb_of_philo)
			sem_wait(p->miam);
	i = -1;
	while (++i < p->nb_of_philo)
	{
		p->philo_tab[i] = fork();
		if (p->philo_tab[i] == 0)
		{
			p->index = i;
			if (p->nb_of_philo != 1)
				pthread_create(&p->checker, NULL, (void *)death_check, p);
			phases(p);
			exit(0);
		}
	}
	return (0);
}

int	sem(t_philo *p)
{
	sem_unlink("fourchette");
	p->fork = sem_open("fourchette", O_CREAT | O_EXCL, 0644, p->nb_of_philo);
	if (p->fork == SEM_FAILED)
		return (1);
	sem_unlink("voix");
	p->voix = sem_open("voix", O_CREAT | O_EXCL, 0644, 1);
	if (p->voix == SEM_FAILED)
		return (1);
	sem_unlink("data_race");
	p->data_race = sem_open("data_race", O_CREAT | O_EXCL, 0644, 1);
	if (p->voix == SEM_FAILED)
		return (1);
	sem_unlink("miam");
	p->miam = sem_open("miam", O_CREAT | O_EXCL, 0644, p->nb_of_philo);
	if (p->miam == SEM_FAILED)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		p;

	if (error_gestion(ac, av))
		return (1);
	p = initializer(av);
	if (sem(&p))
		return (1);
	if (forktab(&p))
		return (1);
	exit_main(&p);
	return (0);
}
