NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

SRCS = main.c \
       parsing.c \
       init.c \
       dinner.c \
       monitor.c \
       write.c \
       utils.c \
       synchro_utils.c \
       getters_setters.c\
       parsing_utils.c

OBJS = $(SRCS:.c=.o)
HEADERS = philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
