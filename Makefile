NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
       parsing.c \
       init.c \
       dinner.c \
       monitor.c \
       write.c \
       utils.c \
       safe_functions.c \
       synchro_utils.c \
       getters_setters.c

OBJS = $(SRCS:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	./$(NAME) 4 300 200 200 5

.PHONY: all clean fclean re test
