SRCS = philo.c pars.c utils.c
OBJS = $(SRCS:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 


all: ${NAME}

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all