/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:31:56 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 17:07:48 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			main(int argc, char *argv[])
{
	t_info				info;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		for_print;
	pthread_mutex_t		for_check;

	if (check_args(argc, argv) == -1)
		return (print_err("Invalid arguments"));
	if ((init_info(argc, argv, &info) == -1) ||
		(!(forks = init_forks(info))))
		return (print_err("Initialization failure"));
	if (!(philos = init_philos(info, forks, &for_print, &for_check)))
	{
		free(forks);
		return (print_err("Initialization failure"));
	}
	start_dining(info, philos);
	free_machine(philos, forks, &for_print, &for_check);
	return (EXIT_SUCCESS);
}
