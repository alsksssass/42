NAME = libftprintf.a
OBJS = $(SRCS:.c=.o)
SRCS = ft_itoa.c ft_pmain.c ft_strcpy.c ft_malloc.c ft_p_option.c ft_s_c_option.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(OBJS)

OBJ_FILES = $(OBJECTS)


all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rcs $(NAME) $(OBJECTS)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
