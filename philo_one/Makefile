# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 14:54:11 by jwon              #+#    #+#              #
#    Updated: 2021/02/11 17:37:10 by jwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_one

SRCS	= init.c \
		  action.c \
		  status.c \
		  utils.c \
		  utils_libft.c \
		  utils_time.c \
		  main.c

OBJS	= ${SRCS:%.c=%.o}

FLAGS	= -Wall -Wextra -Werror

$(NAME):
	gcc $(FLAGS) -c $(SRCS) -I ./
	gcc $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
