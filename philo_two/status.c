/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:26:05 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		is_full(t_philo *philo)
{
	sem_wait(philo->for_eat);
	if (philo->info->num_must_eat != 0 &&
		philo->im_full == FALSE &&
		philo->cnt_eat >= philo->info->num_must_eat)
	{
		sem_post(philo->for_eat);
		philo->im_full = TRUE;
		sem_wait(philo->sems->for_check);
		g_cnt_full_philos++;
		sem_post(philo->sems->for_check);
		return (1);
	}
	sem_post(philo->for_eat);
	return (0);
}

static int		is_die(t_philo *philo)
{
	long		current;

	current = get_current_time();
	sem_wait(philo->for_eat);
	if ((current - philo->time_last_eat) > philo->info->time_to_die)
	{
		sem_post(philo->for_eat);
		print_msg("died", philo);
		sem_wait(philo->sems->for_check);
		g_cnt_dead_philos++;
		sem_post(philo->sems->for_check);
		return (1);
	}
	sem_post(philo->for_eat);
	return (0);
}

void			*check_status(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->sems->for_check);
	while (g_cnt_dead_philos == 0 &&
		g_cnt_full_philos < philo->info->num_philo)
	{
		sem_post(philo->sems->for_check);
		if (is_full(philo))
		{
			sem_wait(philo->sems->for_check);
			continue ;
		}
		if (is_die(philo))
			return (NULL);
		sem_wait(philo->sems->for_check);
	}
	sem_post(philo->sems->for_check);
	return (NULL);
}
