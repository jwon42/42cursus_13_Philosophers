/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:55:12 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 12:34:36 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		party(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->fork_l]);
	print_msg(FORK, philo);
	pthread_mutex_lock(&philo->info->forks[philo->fork_r]);
	print_msg(FORK, philo);
	pthread_mutex_lock(&philo->for_eat);
	print_msg(EAT, philo);
	philo->time_last_eat = get_time();
	philo->cnt_eat++;
	pthread_mutex_unlock(&philo->for_eat);
	ft_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[philo->fork_l]);
	pthread_mutex_unlock(&philo->info->forks[philo->fork_r]);
}

static void		*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->idx % 2)
		ft_sleep(10);
	philo->time_last_eat = get_time();
	while (philo->info->full_or_die == FALSE)
	{
		party(philo);
		if (philo->info->num_must_eat && check_full(philo))
			break ;
		print_msg(SLEEP, philo);
		ft_sleep(philo->info->time_to_sleep);
		print_msg(THINK, philo);
	}
	return (NULL);
}

int				start_dining(t_info *info)
{
	int			idx;
	pthread_t	tid;

	idx = 0;
	info->time_start = get_time();
	while (idx < info->num_philo)
	{
		if (pthread_create(&info->philos[idx].thread, NULL, routine, &info->philos[idx]))
			return (FAILURE);
		idx++;
	}
	pthread_create(&tid, NULL, check_die, info->philos);
	pthread_detach(tid);
	idx = 0;
	while (idx < info->num_philo)
	{
		pthread_join(info->philos[idx].thread, NULL);
		idx++;
	}
	return (SUCCESS);
}
