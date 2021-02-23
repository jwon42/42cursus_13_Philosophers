/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:23:27 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 12:37:34 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

uint64_t	get_time(void)
{
	uint64_t		time;
	struct timeval	tv;

	if ((gettimeofday(&tv, NULL)) == -1)
		return (0);
	time = tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000L;
	return (time);
}

void		ft_sleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	return ;
}
