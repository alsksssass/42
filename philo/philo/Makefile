NAME = philo
SRCS = main.c atoi.c itoa.c strjoin.c bzero.c strdup.c memcpy.c strlen.c strlcpy.c forking_1.c forking_2.c sleep_life.c make_philo.c print.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CC = cc
CFLAGS =-g -Wall -Werror -Wextra
#CFLAGS =-g -fsanitize=address -Wall -Werror -Wextra
#CFLAGS =-g -fsanitize=thread -Wall -Werror -Wextra
RM = rm -rf
MAKE = make

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
