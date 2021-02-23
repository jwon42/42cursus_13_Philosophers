/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:06:58 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 16:20:32 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	sem_wait(philo->info->for_print);
	if (philo->im_dead == FALSE)
	{
		printf("%10lldms | ", get_time() - philo->info->time_start);
		if (status == FULL)
			printf("%s\n", get_msg(status));
		else
			printf("philosopher %d %s\n", philo->idx + 1, get_msg(status));
		if (status == DIE || status == FULL)
			exit(EXIT_SUCCESS);
	}
	sem_post(philo->info->for_print);
}

int				check_args(int argc, char *argv[])
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

void			free_machine(t_info *info)
{
	int		idx;
	int		end;

	idx = 0;
	end = info->num_philo;
	if (info->num_must_eat)
		kill(info->cnt_pid, SIGKILL);
	while (idx < end)
	{
		kill(info->philos[idx].pid, SIGKILL);
		sem_close(info->philos[idx].for_eat);
		sem_unlink(info->philos[idx].for_eat_name);
		sem_close(info->philos[idx].for_full);
		sem_unlink(info->philos[idx].for_full_name);
		idx++;
	}
	free(info->philos);
	sem_close(info->forks);
	sem_unlink("/forks");
	sem_close(info->for_print);
	sem_unlink("/for_print");
}
