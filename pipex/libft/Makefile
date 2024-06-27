NAME = libft.a
OBJS = $(SRCS:.c=.o)
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memset.c ft_strchr.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_memcpy.c ft_strlcat.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_pmain.c ft_malloc.c ft_p_option.c ft_s_c_option.c long_ft_itoa.c get_next_line.c get_next_line_utils.c
BOBJS=$(BSRCS:.c=.o)
BSRCS =ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJECTS = $(OBJS)

OBJECTS_B = $(BOBJS)

OBJ_FILES_B = $(OBJECTS) $(OBJECTS_B)

OBJ_FILES = $(OBJECTS)


all : $(NAME)

$(NAME) : $(OBJ_FILES)
	ar rcs $(NAME) $(OBJECTS)

bonus : BONUS

BONUS : $(OBJ_FILES_B)
	ar rcs $(NAME) $(OBJ_FILES_B)
	touch $@
clean :
	rm -f $(OBJECTS) $(OBJECTS_B) BONUS

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
