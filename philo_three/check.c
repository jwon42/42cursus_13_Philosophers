/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 14:45:41 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		check_full(t_info *info)
{
	int		idx;
	int		cnt;

	cnt = 0;
	while (cnt < info->num_must_eat)
	{
		idx = 0;
		while (idx < info->num_philo)
		{
			sem_wait(info->philos[idx].for_full);
			idx++;
		}
		cnt++;
	}
	print_msg(FULL, info->philos);
}

void		*check_die(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->im_dead == FALSE)
	{
		if (get_time() - philo->time_last_eat > philo->info->time_to_die)
		{
			print_msg(DIE, philo);
			philo->im_dead = TRUE;
		}
		ft_sleep(1);
	}
	return (NULL);
}
