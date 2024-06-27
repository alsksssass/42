NAME = philo_bonus
SRCS = main.c atoi.c itoa.c strjoin.c bzero.c strdup.c memcpy.c strlen.c strlcpy.c multi_fuc.c live.c odd_even.c is_num.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CC = cc
CFLAGS =-Wall -Werror -Wextra
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
