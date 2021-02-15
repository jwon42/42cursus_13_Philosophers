/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:55:12 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:29:00 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		party_time(t_philo *philo)
{
	sem_wait(philo->sems->forks);
	print_msg("has taken a fork", philo);
	sem_wait(philo->sems->forks);
	print_msg("has taken a fork", philo);
	sem_wait(philo->sems->for_eat);
	philo->time_last_eat = get_current_time();
	philo->cnt_eat++;
	print_msg("is eating", philo);
	sem_post(philo->sems->for_eat);
	ft_sleep(philo->info->time_to_eat);
	sem_post(philo->sems->forks);
	sem_post(philo->sems->forks);
}

static void		*main_loop(void *arg)
{
	t_philo			*philo;
	pthread_t		monitor;

	philo = (t_philo *)arg;
	if (philo->idx % 2)
		ft_sleep(philo->info->time_to_eat);
	pthread_create(&monitor, NULL, check_status, arg);
	while (!philo->im_dead)
	{
		party_time(philo);
		print_msg("is sleeping", philo);
		ft_sleep(philo->info->time_to_sleep);
		print_msg("is thinking", philo);
	}
	pthread_detach(monitor);
	return (NULL);
}

void			start_dining(t_info info, t_philo *philos)
{
	int				idx;
	pthread_t		monitor;

	idx = 0;
	sem_wait(philos->sems->for_thread);
	while (idx < info.num_philo)
	{
		philos[idx].pid = fork();
		if (philos[idx].pid == -1)
			break ;
		else if (philos[idx].pid == 0)
			main_loop(&philos[idx]);
		idx++;
	}
	sem_post(philos->sems->for_thread);
	if (info.num_must_eat != 0)
	{
		pthread_create(&monitor, NULL, check_full, philos);
		pthread_detach(monitor);
	}
}
