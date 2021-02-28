/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:44:40 by jwon              #+#    #+#             */
/*   Updated: 2021/02/25 20:22:46 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		init_sems(t_info *info)
{
	sem_unlink("/forks");
	if ((info->forks = sem_open("/forks",
		O_CREAT, 0644, info->num_philo)) == SEM_FAILED)
		return (FAILURE);
	sem_unlink("/for_print");
	if ((info->for_print = sem_open("/for_print",
		O_CREAT, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	sem_unlink("/for_finish");
	if ((info->for_finish = sem_open("/for_finish",
		O_CREAT, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	return (SUCCESS);
}

static int		init_philo_sems(t_info *info, int idx, char *idx_sem)
{
	info->philos[idx].for_eat_name = ft_strjoin("/for_eat_", idx_sem);
	sem_unlink(info->philos[idx].for_eat_name);
	if ((info->philos[idx].for_eat = sem_open(
		info->philos[idx].for_eat_name,
		O_CREAT, 0644, 1)) == SEM_FAILED)
		return (FAILURE);
	free(info->philos[idx].for_eat_name);
	info->philos[idx].for_eat_name = NULL;
	return (SUCCESS);
}

static int		init_philos(t_info *info)
{
	int		idx;

	idx = 0;
	while (idx < info->num_philo)
	{
		info->philos[idx].idx_sem = ft_itoa(idx + 1);
		info->philos[idx].idx = idx;
		if (init_philo_sems(info, idx, info->philos[idx].idx_sem) == FAILURE)
			return (FAILURE);
		free(info->philos[idx].idx_sem);
		info->philos[idx].cnt_eat = 0;
		info->philos[idx].time_last_eat = get_time();
		info->philos[idx].info = info;
		idx++;
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
	info->full_or_die = FALSE;
	info->somebody_full = 0;
	if (init_sems(info) == FAILURE)
		return (FAILURE);
	if (!(info->philos = malloc(sizeof(t_philo) * info->num_philo)))
		return (FAILURE);
	if (init_philos(info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
