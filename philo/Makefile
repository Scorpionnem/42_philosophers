# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 10:49:27 by mbatty            #+#    #+#              #
#    Updated: 2025/04/03 10:15:47 by mbatty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES =	main.c \
			params.c \
			utils.c \
			time_utils.c \
			actions.c \
			philos.c \
			lst_philo.c \
			mutex.c \
			philo_checks.c \
			philo_creation.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

%.o : %.c
		@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJECTS)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
		@echo "\033[0;32mCompiled $(NAME) ✅\033[0m"

clean:
		@rm -f $(OBJECTS)
		@echo "\033[0;32mCleaned objects ✅\033[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[0;32mCleaned everything ✅\033[0m"

re: fclean all

.PHONY: all clean fclean re
