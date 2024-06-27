NAME = pipex
SRCS = src/main.c src/cmd_checker.c src/parsing.c src/set_fd.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
BNS_SRCS = src_bonus/main_bonus.c src_bonus/cmd_checker_bonus.c src_bonus/parsing_bonus.c src_bonus/set_fd_bonus.c
BNS_OBJS = $(BNS_SRCS:.c=.o)
BNS_DEPS = $(BNS_SRCS:.c=.d)
LIBFT_DIR = libft
CC = cc
CFLAGS =-Wall -Werror -Wextra
LIBFT = $(LIBFT_DIR)/libft.a
RM = rm -rf
MAKE = make

all: $(NAME)

bonus: BONUS

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o $@
	$(RM) BONUS

BONUS : $(BNS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BNS_OBJS) -I$(LIBFT_DIR)  -L$(LIBFT_DIR) -lft -o $(NAME)
	touch BONUS

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(LIBFT_DIR) -o $@

$(LIBFT):
	$(MAKE) -sC libft all

clean:
	$(RM) $(OBJS) $(DEPS) $(BNS_OBJS) $(BNS_DEPS)
	$(MAKE) -sC $(LIBFT_DIR) clean
	$(RM) BONUS

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

