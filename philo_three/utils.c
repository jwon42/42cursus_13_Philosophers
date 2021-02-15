/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:06:58 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:16:47 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			print_err(char *str)
{
	printf("Error : %s\n", str);
	return (EXIT_FAILURE);
}

void		print_msg(char *str, t_philo *philo)
{
	long		time;

	time = get_current_time() - philo->time_first_eat;
	if (!philo->im_dead)
	{
		sem_wait(philo->sems->for_print);
		printf("%10ldms | philosopher %d %s\n", time, philo->idx + 1, str);
		sem_post(philo->sems->for_print);
	}
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

void		free_machine(t_philo *philos, t_sems *sems)
{
	int		idx;
	int		end;

	idx = 0;
	end = philos[idx].info->num_philo;
	waitpid(-1, NULL, 0);
	while (idx < end)
	{
		kill(philos[idx].pid, SIGKILL);
		idx++;
	}
	sem_close(sems->forks);
	sem_unlink("/forks");
	sem_close(sems->for_eat);
	sem_unlink("/for_eat");
	sem_close(sems->for_print);
	sem_unlink("/for_print");
	sem_close(sems->for_full);
	sem_unlink("/for_full");
	sem_close(sems->for_thread);
	sem_unlink("/for_thread");
}
