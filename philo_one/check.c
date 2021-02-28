/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 17:18:15 by jwon              #+#    #+#             */
/*   Updated: 2021/02/24 15:56:30 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			check_full(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->for_eat);
	if (philo->cnt_eat == philo->info->num_must_eat)
		philo->info->somebody_full++;
	pthread_mutex_unlock(&philo->for_eat);
	if (philo->info->somebody_full == philo->info->num_philo)
	{
		print_msg(FULL, philo);
		pthread_mutex_lock(&philo->info->for_finish);
		philo->info->full_or_die = TRUE;
		pthread_mutex_unlock(&philo->info->for_finish);
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
			pthread_mutex_lock(&philo->info->for_finish);
			philo->info->full_or_die = TRUE;
			pthread_mutex_unlock(&philo->info->for_finish);
			break ;
		}
		ft_sleep(1);
	}
	return (NULL);
}
