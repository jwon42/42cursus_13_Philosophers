/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:55:12 by jwon              #+#    #+#             */
/*   Updated: 2021/02/28 19:01:14 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void		party(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_msg(FORK, philo);
	sem_wait(philo->info->forks);
	print_msg(FORK, philo);
	sem_wait(philo->for_eat);
	print_msg(EAT, philo);
	philo->time_last_eat = get_time();
	philo->cnt_eat++;
	sem_post(philo->for_eat);
	ft_sleep(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void		*routine(void *arg)
{
	t_philo			*philo;
	pthread_t		tid;

	philo = (t_philo *)arg;
	if (pthread_create(&tid, NULL, &check_status, philo))
		return (NULL);
	philo->time_last_eat = get_time();
	while (42)
	{
		party(philo);
		print_msg(SLEEP, philo);
		ft_sleep(philo->info->time_to_sleep);
		print_msg(THINK, philo);
	}
	pthread_detach(tid);
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
		info->philos[idx].pid = fork();
		if (info->philos[idx].pid == -1)
			break ;
		else if (info->philos[idx].pid == 0)
			routine(&info->philos[idx]);
		idx++;
	}
	if (info->num_must_eat)
	{
		pthread_create(&tid, NULL, check_full, &info->philos[0]);
		pthread_detach(tid);
	}
	waitpid(-1, NULL, 0);
	return (SUCCESS);
}
