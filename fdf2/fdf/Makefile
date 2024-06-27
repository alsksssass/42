NAME:=a.out
INCS:=fdf.h
LIBFT:=ft
SRCS = fdf.c
LIBFT_DIR:=libft
CC:=cc
CFLAGS:=-Wall -Wextra -Werror 
MFLAG:= -g -fsanitize=address -lmlx -framework OpenGL -framework AppKit -framework OpenGL

all : $(NAME) 

$(NAME) : $(INCS) $(SRCS) 
	@make -sC $(LIBFT_DIR) all
	$(CC) -o $@ $(SRCS) -I $(LIBFT_DIR) -L $(LIBFT_DIR) -l$(LIBFT) $(MFLAG)

clean :
	make -C $(LIBFT_DIR) fclean

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
