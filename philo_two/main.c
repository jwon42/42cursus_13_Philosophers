/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:31:56 by jwon              #+#    #+#             */
/*   Updated: 2021/02/23 12:37:15 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			main(int argc, char *argv[])
{
	t_info				info;

	if (init(argc, argv, &info) == FAILURE)
		return (print_err("Initialization failure"));
	if ((start_dining(&info)) == FAILURE)
		return (print_err("Fatal exception"));
	free_machine(&info);
	return (EXIT_SUCCESS);
}
