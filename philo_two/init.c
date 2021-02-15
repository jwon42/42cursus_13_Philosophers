/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:01:14 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	sem_unlink("/for_print");
	if ((sems->for_print = sem_open("/for_print",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("/for_check");
	if ((sems->for_check = sem_open("/for_check",
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
		philos[idx].sem_idx = ft_itoa(idx + 1);
		philos[idx].for_eat_name = ft_strjoin("/for_eat_", philos[idx].sem_idx);
		sem_unlink(philos[idx].for_eat_name);
		if ((philos[idx].for_eat = sem_open(philos[idx].for_eat_name,
			O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
			return (NULL);
		philos[idx].time_first_eat = get_current_time();
		philos[idx].time_last_eat = get_current_time();
		philos[idx].cnt_eat = 0;
		philos[idx].im_full = FALSE;
		philos[idx].info = &info;
		philos[idx].sems = sems;
		idx++;
	}
	return (philos);
}
