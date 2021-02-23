/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 13:03:42 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			check_full(void *arg)
{
	t_philo	*philo;

	philo = arg;
	sem_wait(philo->for_eat);
	if (philo->cnt_eat == philo->info->num_must_eat)
		philo->info->somebody_full++;
	sem_post(philo->for_eat);
	if (philo->info->somebody_full == philo->info->num_philo)
	{
		print_msg(FULL, philo);
		philo->info->full_or_die = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void		*check_die(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->info->full_or_die == FALSE)
	{
		if (get_time() - philo->time_last_eat > philo->info->time_to_die)
		{
			print_msg(DIE, philo);
			philo->info->full_or_die = TRUE;
			break ;
		}
		ft_sleep(1);
	}
	return (NULL);
}
