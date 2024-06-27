NAME = push_swap
BNS_NAME = checker
SRCS = src/main.c src/tiny_b_to_a.c src/tiny_a_to_b.c src/small_swap.c src/small_swap_2.c src/default_set_1.c src/default_set_2.c src/free.c src/quick_sort.c src/stack_maker.c src/stack_sort.c src/stack_sort_2.c src/swap.c src/swap_3.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
BNS_SRCS = src_bonus/main_bonus.c src_bonus/malloc_bonus.c src_bonus/stack_bonus.c src_bonus/swap_bonus.c src_bonus/default_bonus.c src_bonus/quick_sort_bonus.c src_bonus/transfer_bonus.c 
BNS_OBJS = $(BNS_SRCS:.c=.o)
BNS_DEPS = $(BNS_SRCS:.c=.d)
LIBFT_DIR = libft
CC = cc
CFLAGS =-Wall -Werror -Wextra
LIBFT = $(LIBFT_DIR)/libft.a
RM = rm -rf
MAKE = make

all: $(NAME)

bonus: $(BNS_NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o $@

$(BNS_NAME): $(BNS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BNS_OBJS) -I$(LIBFT_DIR)  -L$(LIBFT_DIR) -lft -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(LIBFT_DIR) -o $@

$(LIBFT):
	$(MAKE) -sC libft all

clean:
	$(RM) $(OBJS) $(DEPS) $(BNS_OBJS) $(BNS_DEPS)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BNS_NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

