/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:23:27 by jwon              #+#    #+#             */
/*   Updated: 2021/02/11 15:32:06 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long		get_current_time(void)
{
	long			time;
	struct timeval	tv;

	if ((gettimeofday(&tv, NULL)) == -1)
		return (0);
	time = tv.tv_sec * 1000L + tv.tv_usec / 1000L;
	return (time);
}

void		ft_sleep(long time)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(100);
	return ;
}
