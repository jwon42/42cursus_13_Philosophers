/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:23:42 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->for_eat);
	if (philo->info->num_must_eat != 0 &&
		philo->is_full == FALSE &&
		philo->cnt_eat >= philo->info->num_must_eat)
	{
		pthread_mutex_unlock(&philo->for_eat);
		philo->is_full = TRUE;
		pthread_mutex_lock(philo->for_check);
		g_cnt_full_philos++;
		pthread_mutex_unlock(philo->for_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->for_eat);
	return (0);
}

static int		is_die(t_philo *philo)
{
	long		time;

	time = get_current_time();
	pthread_mutex_lock(&philo->for_eat);
	if ((time - philo->time_last_eat) > philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->for_eat);
		print_msg("died", philo);
		pthread_mutex_lock(philo->for_check);
		g_cnt_dead_philos++;
		pthread_mutex_unlock(philo->for_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->for_eat);
	return (0);
}

void			*check_status(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->for_check);
	while (g_cnt_dead_philos == 0 &&
		g_cnt_full_philos < philo->info->num_philo)
	{
		pthread_mutex_unlock(philo->for_check);
		if (is_full(philo))
		{
			pthread_mutex_lock(philo->for_check);
			continue ;
		}
		if (is_die(philo))
			return (NULL);
		pthread_mutex_lock(philo->for_check);
	}
	pthread_mutex_unlock(philo->for_check);
	return (NULL);
}
