/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 15:52:38 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int			init_mutexes(t_info *info)
{
	int		idx;

	pthread_mutex_init(&info->for_print, NULL);
	if (!(info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo)))
		return (FAILURE);
	idx = 0;
	while (idx < info->num_philo)
	{
		pthread_mutex_init(&(info->forks[idx]), NULL);
		idx++;
	}
	return (SUCCESS);
}

static void		init_philos(t_info *info)
{
	int		idx;

	idx = 0;
	while (idx < info->num_philo)
	{
		info->philos[idx].idx = idx;
		info->philos[idx].fork_l = idx;
		info->philos[idx].fork_r = (idx + 1) % info->num_philo;
		pthread_mutex_init(&info->philos[idx].for_eat, NULL);
		info->philos[idx].cnt_eat = 0;
		info->philos[idx].time_last_eat = get_time();
		info->philos[idx].info = info;
		idx++;
	}
}

int				init(int argc, char *argv[], t_info *info)
{
	if ((check_args(argc, argv) == FAILURE) ||
		((info->num_philo = ft_atoi(argv[1])) < 2) ||
		((info->time_to_die = (long)ft_atoi(argv[2])) < 1) ||
		((info->time_to_eat = (long)ft_atoi(argv[3])) < 1) ||
		((info->time_to_sleep = (long)ft_atoi(argv[4])) < 1))
		return (FAILURE);
	if (argc == 6)
	{
		if ((info->num_must_eat = (long)ft_atoi(argv[5])) < 1)
			return (FAILURE);
	}
	else
		info->num_must_eat = 0;
	info->full_or_die = FALSE;
	info->somebody_full = 0;
	if (!(info->philos = malloc(sizeof(t_philo) * info->num_philo)))
		return (FAILURE);
	if (init_mutexes(info) == FAILURE)
		return (FAILURE);
	init_philos(info);
	return (SUCCESS);
}
