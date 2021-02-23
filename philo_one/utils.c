/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:06:58 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 08:09:05 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				print_err(char *str)
{
	printf("Error : %s\n", str);
	return (EXIT_FAILURE);
}

static char		*get_msg(int status)
{
	if (status == FORK)
		return ("has taken a fork");
	else if (status == EAT)
		return ("is eating");
	else if (status == SLEEP)
		return ("is sleeping");
	else if (status == THINK)
		return ("is thinking");
	else if (status == DIE)
		return ("died");
	else if (status == FULL)
		return ("All philosophers have finished eating :)");
	return (NULL);
}

void			print_msg(int status, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->for_print);
	if (philo->info->full_or_die == FALSE)
	{
		printf("%10lldms | ", get_time() - philo->info->time_start);
		if (status == FULL)
			printf("%s\n", get_msg(status));
		else
			printf("philosopher %d %s\n", philo->idx + 1, get_msg(status));
		if (status == DIE || status == FULL)
		{
			philo->info->full_or_die = TRUE;
			pthread_mutex_unlock(&philo->info->for_print);
			return ;
		}
	}
	pthread_mutex_unlock(&philo->info->for_print);
}

int			check_args(int argc, char *argv[])
{
	int		idx_arg;
	int		idx_chr;

	if (argc != 5 && argc != 6)
		return (-1);
	idx_arg = 1;
	while (argv[idx_arg])
	{
		idx_chr = 0;
		while (argv[idx_arg][idx_chr])
		{
			if (!(ft_isdigit(argv[idx_arg][idx_chr])))
				return (-1);
			idx_chr++;
		}
		idx_arg++;
	}
	return (0);
}

void		free_machine(t_info *info)
{
	int		idx;
	int		end;

	idx = 0;
	end = info->num_philo;
	if (info)
	{
		if (info->forks)
		{
			while (idx < end)
				pthread_mutex_destroy(&info->forks[idx++]);
			free(info->forks);
		}
		pthread_mutex_destroy(&info->for_print);
		if (info->philos)
		{
			idx = 0;
			while (idx < end)
				pthread_mutex_destroy(&info->philos[idx++].for_eat);
			free(info->philos);
			info->philos = NULL;
		}
	}
}
