/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:19:09 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/06/09 20:32:47 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# define BLK "\e[0;90m"
# define RED "\e[0;91m"
# define GRN "\e[0;92m"
# define YEL "\e[0;93m"
# define BLU "\e[0;94m"
# define MAG "\e[0;95m"
# define CYN "\e[0;96m"
# define WHT "\e[0;97m"

# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef int	t_boolean;
# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t		food;
	pthread_t		checker;
	size_t			start;
	int				index;
	t_boolean		*is_full;
	t_boolean		is_dead;
	t_boolean		meals_end;
	pid_t			*philo_tab;
	struct timeval	last_meal;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				as_eaten;
	int				status;
	t_boolean		success;
	sem_t			*fork;
	sem_t			*voix;
	sem_t			*data_race;
	sem_t			*miam;
}	t_philo;

typedef struct s_values
{
	int		prev;
	int		index;
	int		nb_of_meals;
}	t_values;

/*		UTILITIES		*/

size_t	gtime(void);
void	ft_sleep(int timeobj, t_philo *p);
t_philo	initializer(char **av);
void	exit_main(t_philo *p);
void	*eat(t_philo *p);

/*		ERROR_MANAGEMENT		*/

int		error_gestion(int ac, char **av);
long	ft_atol(const char *str);

/*		END CHECKER			*/

void	*death_check(t_philo *arg);

/*		PHASES			*/

void	*phases(t_philo *p);

#endif
