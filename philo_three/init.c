/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 18:43:16 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int					init_sems(t_info info, t_sems *sems)
{
	sem_unlink("/forks");
	if ((sems->forks = sem_open("/forks",
		O_CREAT | O_EXCL, 0644, info.num_philo)) == SEM_FAILED)
		return (-1);
	sem_unlink("/for_eat");
	if ((sems->for_eat = sem_open("/for_eat",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("/for_print");
	if ((sems->for_print = sem_open("/for_print",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("/for_full");
	if ((sems->for_full = sem_open("/for_full",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("/for_thread");
	if ((sems->for_thread = sem_open("/for_thread",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

t_philo				*init_philos(t_info info, t_sems *sems)
{
	int			idx;
	t_philo		*philos;

	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * info.num_philo)))
		return (NULL);
	idx = 0;
	while (idx < info.num_philo)
	{
		philos[idx].idx = idx;
		philos[idx].time_first_eat = get_current_time();
		philos[idx].time_last_eat = get_current_time();
		philos[idx].cnt_eat = 0;
		philos[idx].im_dead = FALSE;
		philos[idx].im_full = FALSE;
		philos[idx].info = &info;
		philos[idx].sems = sems;
		idx++;
	}
	return (philos);
}
