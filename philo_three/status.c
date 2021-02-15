/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:28:30 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		is_full(t_philo *philo)
{
	if (philo->im_full == FALSE &&
		philo->info->num_must_eat != 0 &&
		philo->cnt_eat >= philo->info->num_must_eat)
	{
		sem_post(philo->sems->for_full);
		philo->im_full = TRUE;
		return (1);
	}
	return (0);
}

static void		is_die(t_philo *philo)
{
	long		current;

	current = get_current_time();
	if ((current - philo->time_last_eat) > philo->info->time_to_die)
	{
		print_msg("died", philo);
		philo->im_dead = TRUE;
		exit(EXIT_SUCCESS);
	}
}

void			*check_status(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (!philo->im_dead)
	{
		if (is_full(philo))
			continue ;
		is_die(philo);
	}
	return (NULL);
}

void			*check_full(void *arg)
{
	int				idx;
	int				cnt_eat;
	t_philo			*philo;

	philo = (t_philo *)arg;
	cnt_eat = 0;
	while (1)
	{
		sem_wait(philo->sems->for_full);
		if (cnt_eat == philo->info->num_philo)
		{
			idx = 0;
			while (idx < philo->info->num_philo)
			{
				kill(philo[idx].pid, SIGKILL);
				idx++;
			}
			break ;
		}
		cnt_eat++;
	}
	return (NULL);
}
