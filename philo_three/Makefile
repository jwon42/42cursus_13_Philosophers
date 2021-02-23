# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 14:54:11 by jwon              #+#    #+#              #
#    Updated: 2021/02/23 13:46:33 by jwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_three

SRCS	= init.c \
		  action.c \
		  check.c \
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
