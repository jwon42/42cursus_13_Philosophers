/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:23:59 by jwon              #+#    #+#             */
/*   Updated: 2021/02/24 15:56:30 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAILURE -1

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FULL 5

struct s_info;

typedef struct			s_philo
{
	int					idx;
	pthread_t			thread;

	int					fork_l;
	int					fork_r;

	int					cnt_eat;
	uint64_t			time_last_eat;

	pthread_mutex_t		for_eat;

	struct s_info		*info;
}						t_philo;

typedef struct			s_info
{
	int					num_philo;
	uint64_t			time_to_die;
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	int					num_must_eat;

	uint64_t			time_start;

	int					full_or_die;
	int					somebody_full;

	pthread_mutex_t		*forks;
	pthread_mutex_t		for_print;
	pthread_mutex_t		for_finish;

	t_philo				*philos;
}						t_info;

/*
** init.c
*/
int						init(int argc, char *argv[], t_info *info);

/*
** action.c
*/
int						start_dining(t_info *info);

/*
** check.c
*/
int						check_full(void *arg);
void					*check_die(void *arg);

/*
** utils_libft.c
*/
int						ft_isdigit(int c);
int						ft_atoi(const char *str);

/*
** utils_time.c
*/
uint64_t				get_time(void);
void					ft_sleep(uint64_t time);

/*
** utils.c
*/
int						print_err(char *str);
void					print_msg(int status, t_philo *philo);
int						check_args(int argc, char *argv[]);
void					free_machine(t_info *info);

#endif
