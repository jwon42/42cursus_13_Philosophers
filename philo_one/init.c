/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/12 00:42:24 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					init_info(int argc, char *argv[], t_info *info)
{
	if ((info->num_philo = ft_atoi(argv[1])) < 2)
		return (-1);
	if ((info->time_to_die = (long)ft_atoi(argv[2])) < 1)
		return (-1);
	if ((info->time_to_eat = (long)ft_atoi(argv[3])) < 1)
		return (-1);
	if ((info->time_to_sleep = (long)ft_atoi(argv[4])) < 1)
		return (-1);
	if (argc == 6)
	{
		if ((info->num_must_eat = (long)ft_atoi(argv[5])) < 1)
			return (-1);
	}
	else
		info->num_must_eat = 0;
	return (0);
}

pthread_mutex_t		*init_forks(t_info info)
{
	int					idx;
	pthread_mutex_t		*forks;

	if (!(forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
		info.num_philo)))
		return (NULL);
	idx = 0;
	while (idx < info.num_philo)
	{
		pthread_mutex_init(&(forks[idx]), NULL);
		idx++;
	}
	return (forks);
}

t_philo				*init_philos
(
	t_info info,
	pthread_mutex_t *forks,
	pthread_mutex_t *for_print,
	pthread_mutex_t *for_check
)
{
	int					idx;
	t_philo				*philos;

	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * info.num_philo)))
		return (NULL);
	pthread_mutex_init(for_print, NULL);
	pthread_mutex_init(for_check, NULL);
	idx = 0;
	while (idx < info.num_philo)
	{
		philos[idx].idx = idx;
		philos[idx].fork_left = &forks[idx];
		philos[idx].fork_right = &forks[(idx + 1) % info.num_philo];
		pthread_mutex_init(&philos[idx].for_eat, NULL);
		philos[idx].for_print = for_print;
		philos[idx].for_check = for_check;
		philos[idx].time_first_eat = get_current_time();
		philos[idx].time_last_eat = get_current_time();
		philos[idx].cnt_eat = 0;
		philos[idx].is_full = FALSE;
		philos[idx].info = &info;
		idx++;
	}
	return (philos);
}
