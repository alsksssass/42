NAME = minishell 
SRCS = src/main.c src/builtin.c src/env.c src/do_cmd.c src/ft_splitset.c src/make_node.c src/to_char.c src/here_doc_single_re.c src/eof_doller_recover.c src/find_doller.c src/split_cmd.c src/str_int.c src/triple_strcmp.c src/qq_note.c src/ft_stcmp.c src/is_open.c src/cmd_process.c src/do_cmd_set.c src/env_get.c src/env_path.c src/error_fuc.c src/get_env.c src/make_env.c src/standard_fuc.c src/standard_fuc2.c src/syntax_check.c src/pwd.c src/for_env_func.c src/remove_file.c src/inoutfile.c src/fd_open.c src/single_fd_set.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
LIBFT_DIR = libft
CC = cc
CFLAGS =-g -Wall -Werror -Wextra 
MDOP = -MMD -MP
ADDLIB = -lreadline
LIBFT = $(LIBFT_DIR)/libft.a
RM = rm -rf
MAKE = make

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MDOP) $(ADDLIB) $(OBJS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(MDOP) -c $< -I$(LIBFT_DIR) -o $@

$(LIBFT):
	$(MAKE) -sC libft all

clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) -sC $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

