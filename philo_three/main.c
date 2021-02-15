/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:31:56 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:27:38 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			main(int argc, char *argv[])
{
	t_info				info;
	t_sems				sems;
	t_philo				*philos;

	if (check_args(argc, argv) == -1)
		return (print_err("Invalid arguments"));
	if ((init_info(argc, argv, &info) == -1) ||
		(init_sems(info, &sems) == -1) ||
		(!(philos = init_philos(info, &sems))))
		return (print_err("Initialization failure"));
	start_dining(info, philos);
	free_machine(philos, &sems);
	return (EXIT_SUCCESS);
}
