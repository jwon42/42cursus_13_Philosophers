/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 16:23:59 by jwon              #+#    #+#             */
/*   Updated: 2021/02/15 19:25:41 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <errno.h>

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

typedef struct			s_sems
{
	sem_t				*forks;
	sem_t				*for_print;
	sem_t				*for_check;
}						t_sems;

typedef struct			s_philo
{
	int					idx;
	char				*sem_idx;
	char				*for_eat_name;
	sem_t				*for_eat;
	long				time_first_eat;
	long				time_last_eat;
	int					cnt_eat;
	int					im_full;
	t_info				*info;
	t_sems				*sems;
	pthread_t			thread;
}						t_philo;

/*
** init.c
*/
int						init_info(int argc, char *argv[], t_info *info);
int						init_sems(t_info info, t_sems *sems);
t_philo					*init_philos(t_info info, t_sems *sems);

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
size_t					ft_strlen(const char *str);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
char					*ft_strjoin(char const *s1, char const *s2);

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
void					free_machine(t_philo *philos, t_sems *sems);

#endif
