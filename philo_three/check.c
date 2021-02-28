/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/28 20:05:10 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*check_full(void *arg)
{
	int			cnt;
	t_philo		*philo;

	philo = (t_philo *)arg;
	cnt = 0;
	while (42)
	{
		sem_wait(philo->info->for_full);
		if (cnt == philo->info->num_philo)
			break ;
		cnt++;
	}
	print_msg(FULL, philo);
	return (NULL);
}

void		*check_status(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		if (philo->info->num_must_eat &&
			philo->cnt_eat == philo->info->num_must_eat &&
			philo->im_full == FALSE)
		{
			sem_post(philo->info->for_full);
			philo->im_full = TRUE;
		}
		if (get_time() - philo->time_last_eat > philo->info->time_to_die)
			print_msg(DIE, philo);
		ft_sleep(1);
	}
	return (NULL);
}
