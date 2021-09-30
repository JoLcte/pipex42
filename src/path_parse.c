/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 08:24:04 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/30 23:14:06 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_next_path(char *path, int *i)
{
	const int	j = *i;

	if (!path[j])
		return (NULL);
	while (path[*i] != ':' && path[*i])
		++*i;
	if (path[*i])
	{
		path[*i] = '\0';
		++*i;
	}
	return (path + j);
}

/*
**	--- Creation of the path/cmd for execve
**	Note: if cmd is already set with the folder, we don't use ft_strjoin
*/

char	*get_cmd_path(char *cmd, char *env_path)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	if (!ft_strchr(cmd, '/'))
	{
		path = get_next_path(env_path, &i);
		while (path)
		{
			tmp = ft_strjoin(path, "/");
			path = ft_strjoin(tmp, cmd);
			free(tmp);
			if (path && !access(path, F_OK))
				return (path);
			free(path);
			path = get_next_path(env_path, &i);
		}
	}
	else if (!access(cmd, F_OK))
		path = cmd;
	return (path);
}

char	*get_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
			break ;
		++env;
	}
	if (!*env)
		err_exit("Variable PATH not found", "env", 1);
	return (*env + 5);
}
