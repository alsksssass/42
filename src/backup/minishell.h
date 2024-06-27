# ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>

typedef enum e_enum
{
	FALSE,
	TRUE
}t_enum;

typedef struct s_main
{
	struct s_cmd *cmd;
	char *char_set;
	int set_num;

}t_main;

typedef struct s_split
{
        int i;
        int cmd;
        int char_set;
        char **send;
		char *str;

} t_split;

typedef struct s_count
{
    int set;
    int cmd;
    int j;
    int k;
    int i;
	char **str;
	char *string;

}t_count;

typedef struct s_check
{
	int here_doc;
	int here_doc_mark;
	int q_mark;
	int qq_mark;
	int re_direction_mark;
	int error;
	int export;
	struct s_check *next;

}t_check;

typedef struct s_cmd
{
	char *infile;
	char *outfile;
	char **cmd;
	char *here_doc;
	int append;
	struct s_cmd *next;
}t_cmd;

# endif
