/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:06:58 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:17:19 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			print_err(char *str)
{
	printf("Error : %s\n", str);
	return (EXIT_FAILURE);
}

void		print_msg(char *str, t_philo *philo)
{
	long		time;

	time = get_current_time() - philo->time_first_eat;
	pthread_mutex_lock(philo->for_check);
	if (g_cnt_dead_philos == 0 &&
		g_cnt_full_philos < philo->info->num_philo)
	{
		pthread_mutex_unlock(philo->for_check);
		pthread_mutex_lock(philo->for_print);
		printf("%10ldms | philosopher %d %s\n", time, philo->idx + 1, str);
		pthread_mutex_unlock(philo->for_print);
		return ;
	}
	pthread_mutex_unlock(philo->for_check);
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

void		free_machine
(
	t_philo *philos,
	pthread_mutex_t *forks,
	pthread_mutex_t *for_print,
	pthread_mutex_t *for_check
)
{
	int		idx;
	int		end;

	idx = 0;
	end = philos[idx].info->num_philo;
	while (idx < end)
	{
		pthread_mutex_destroy(&forks[idx]);
		pthread_mutex_destroy(&philos[idx].for_eat);
		idx++;
	}
	pthread_mutex_destroy(for_print);
	pthread_mutex_destroy(for_check);
	free(philos);
	free(forks);
}
