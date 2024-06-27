 #include "minishell.h"
 
t_envp *make_envpnode(char *key, char *value)
{
	t_envp *send;
	
	send = ft_calloc(sizeof(t_envp),1);
	send->key = key;
	send->value = value;
	return (send);
}

void add_envpnode(t_envp **envp, t_envp *new)
{
	t_envp  *list;

    if (envp == 0)
        return ;
    if (*envp == 0)
    {
        *envp = new;
        return ;
    }
    list = *envp;
    while (list->next != 0)
        list = list->next;
    list->next = new;
}

int delete_env(t_main *main, char *key)
{
	t_envp *env;
	t_envp *temp;
	env = main->envp_list;

	while(env)
	{
		if (ft_strncmp(env->key,key,ft_strlen(key)+1) == 0)
		{
			if (env == main->envp_list)
			{
				temp = env;
				main->envp_list = env->next;
				free(temp);
			}
			else
			{
				temp->next = env->next;
				free(env);
			}
			return 1;
		}
		temp = env;
		env = env->next;
	}
	return 0;
}
int check_key_able(char *str)
{
	char *msg;

	msg = str;

	if (ft_isdigit(*str) == 1 || !str)
	{
		ft_putstr_fd(msg,2);
		ft_putstr_fd(" not a valid identifier\n",2);
		return 1;
	}
	while (*str)
	{
		if (!(ft_isalnum(*str) == 1 || *str == '_'))
		{
			ft_putstr_fd(msg,2);
			ft_putstr_fd(" not a valid identifier\n",2);
			return 1;
		}
		str++;
	}
	return 0;
}
int check_already_add(t_main *main, char *key, char *value)
{
	t_envp  *list;
	
	list = main->envp_list;
    if (list == 0)
        return 0;
	if (check_key_able(key) == 1)
	{
		free(key);
		free(value);
		return 1;
	}
    while (list)
	{
     	if (ft_strncmp(list->key,key,ft_strlen(list->key) + 1) == 0)
		{
			if (value)
			{
				free(list->value);
				list->value = value;
			}
			free(key);
			return 1;
		}
		list = list->next;
	}
	return 0;
}

void make_envp(t_main *main, char *arr)
{
	char *str;
	char *key;
	char *value;
	
	str = ft_strchr(arr, '=');
	if (str == 0 || str == arr)
	{
		key = ft_strdup(arr);
		value = 0;
	}
	else
	{
		key = ft_substr(arr, 0, str - arr);
		value = ft_substr(arr,  str - arr +1, ft_strlen(str +1));
		value = value_check(value);
	}
	if (check_already_add(main,key,value) == 1)
		return;
	add_envpnode(&main->envp_list,make_envpnode(key,value));
}
void defult_envp(t_main *main)
{
	char **envp;
	int i;
	i = 0;
	envp = main->envp;
	while(envp[i])
	{
		make_envp(main,envp[i]);
		i++;
	}
}
void print_envp(t_main *main, int env)
{
	t_envp *envp;

	envp = main->envp_list;

	while(envp)
	{
		if (env ==0)
			ft_printf("declare -x ");
		ft_printf("%s",envp->key);
		if(envp->value != 0)
		{
			ft_printf("=");
			if(env == 0)
				ft_printf("\"");
			ft_printf("%s",envp->value);
			if(env == 0)
				ft_printf("\"");
		}
		ft_printf("\n");
		envp = envp->next;
	}
}
