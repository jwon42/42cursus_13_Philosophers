/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:55:12 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:03:36 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		party_time(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(philo->fork_right);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->for_eat);
	philo->time_last_eat = get_current_time();
	philo->cnt_eat++;
	print_msg("is eating", philo);
	pthread_mutex_unlock(&philo->for_eat);
	ft_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

static void		*main_loop(void *arg)
{
	t_philo			*philo;
	pthread_t		monitor;

	philo = (t_philo *)arg;
	if (philo->idx % 2)
		ft_sleep(philo->info->time_to_eat);
	pthread_create(&monitor, NULL, check_status, arg);
	pthread_mutex_lock(philo->for_check);
	while (g_cnt_dead_philos == 0 &&
		g_cnt_full_philos < philo->info->num_philo)
	{
		pthread_mutex_unlock(philo->for_check);
		party_time(philo);
		print_msg("is sleeping", philo);
		ft_sleep(philo->info->time_to_sleep);
		print_msg("is thinking", philo);
		pthread_mutex_lock(philo->for_check);
	}
	pthread_mutex_unlock(philo->for_check);
	pthread_detach(monitor);
	return (NULL);
}

void			start_dining(t_info info, t_philo *philos)
{
	int		idx;

	idx = 0;
	while (idx < info.num_philo)
	{
		pthread_create(&philos[idx].thread, NULL, main_loop, &philos[idx]);
		idx++;
	}
	idx = 0;
	while (idx < info.num_philo)
	{
		pthread_join(philos[idx].thread, NULL);
		idx++;
	}
}
