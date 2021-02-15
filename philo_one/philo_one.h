/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:23:59 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 17:07:48 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

int						g_cnt_dead_philos;
int						g_cnt_full_philos;

typedef struct			s_info
{
	int					num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					num_must_eat;
}						t_info;

typedef struct			s_philo
{
	int					idx;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		for_eat;
	pthread_mutex_t		*for_print;
	pthread_mutex_t		*for_check;
	long				time_first_eat;
	long				time_last_eat;
	int					cnt_eat;
	int					is_full;
	t_info				*info;
	pthread_t			thread;
}						t_philo;

/*
** init.c
*/
int						init_info(int argc, char *argv[], t_info *info);
pthread_mutex_t			*init_forks(t_info info);
t_philo					*init_philos(t_info info,
									pthread_mutex_t *forks,
									pthread_mutex_t *for_print,
									pthread_mutex_t *for_check);

/*
** action.c
*/
void					start_dining(t_info info, t_philo *philos);

/*
** check.c
*/
void					*check_status(void *arg);

/*
** utils_libft.c
*/
int						ft_isdigit(int c);
int						ft_atoi(const char *str);

/*
** utils_time.c
*/
long					get_current_time(void);
void					ft_sleep(long time);

/*
** utils.c
*/
int						print_err(char *str);
void					print_msg(char *str, t_philo *philo);
int						check_args(int argc, char *argv[]);
void					free_machine(t_philo *philos,
									pthread_mutex_t *forks,
									pthread_mutex_t *for_print,
									pthread_mutex_t *for_check);

#endif
