NAME = philo_bonus

SOURCES =	main.c params.c utils.c time_utils.c actions.c philos.c

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
