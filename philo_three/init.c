/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/28 20:05:50 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int		init_sems(t_info *info)
{
	sem_unlink("/forks");
	if ((info->forks = sem_open("/forks",
		O_CREAT | O_EXCL, 0644, info->num_philo)) == SEM_FAILED)
		return (FAILURE);
	sem_unlink("/for_full");
	if ((info->for_full = sem_open("/for_full",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	sem_unlink("/for_print");
	if ((info->for_print = sem_open("/for_print",
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	return (SUCCESS);
}

static int		init_philo_sems(t_info *info, int idx)
{
	info->philos[idx].idx_sem = ft_itoa(idx + 1);
	info->philos[idx].for_eat_name = ft_strjoin("/for_eat_",
												info->philos[idx].idx_sem);
	sem_unlink(info->philos[idx].for_eat_name);
	if ((info->philos[idx].for_eat = sem_open(
		info->philos[idx].for_eat_name,
		O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	free(info->philos[idx].for_eat_name);
	free(info->philos[idx].idx_sem);
	return (SUCCESS);
}

static int		init_philos(t_info *info)
{
	int		idx;

	idx = -1;
	while (++idx < info->num_philo)
	{
		info->philos[idx].idx = idx;
		if (init_philo_sems(info, idx) == FAILURE)
			return (FAILURE);
		info->philos[idx].im_full = FALSE;
		info->philos[idx].cnt_eat = 0;
		info->philos[idx].time_last_eat = get_time();
		info->philos[idx].info = info;
	}
	return (SUCCESS);
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
	if (init_sems(info) == FAILURE)
		return (FAILURE);
	if (!(info->philos = malloc(sizeof(t_philo) * info->num_philo)))
		return (FAILURE);
	if (init_philos(info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
