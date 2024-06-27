/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabyun <sabyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:33:34 by sabyun            #+#    #+#             */
/*   Updated: 2024/03/09 18:01:32 by sabyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	relative_absolute_path(char *path)
{
	struct stat	buf;

	if (access(path, F_OK) != 0)
		return (ret_msg(path, "No such file or directory", 127));
	if (access(path, X_OK) != 0)
		return (ret_msg(path, "Permission denied", 126));
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
		return (ret_msg(path, "is a directory", 126));
	return (0);
}

int	ret_msg(char *cmd, char *msg, int code)
{
	print_error(cmd, msg);
	return (code);
}
