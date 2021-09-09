/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 08:24:04 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/09 18:07:44 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_mini_path(char *path, int *i)
{
	const int j = *i;

	if (!path[*i])
		return (0);
	while (path[*i] != ':')
		++*i;
	if (path[*i])
	{
		path[*i] = 0;
		++*i;
	}
	return (path + j);
}

char	*get_path(char **env)
{
	while (*env)
		if (ft_strncmp("PATH=", *env, 5))
			++env;
	if (*env)
		return (*env + 5);
	else
	{
		printf("env: PATH not found\n");
		exit(EXIT_FAILURE);
	}
}

char	*get_cmd_path(char *cmd, char *env_path)
{
	char *path;
	int i;

	i = 0;
	path =	0;
	if (!ft_strchr(cmd, '\''))
	{
		path = get_mini_path(env_path, &i);
		while (path)
		{
			path = ft_strjoin(path, "/");
			//on a des free loupes la
			path = ft_strjoin(path, cmd);
			if (path && !access(path, F_OK))
				return (path);
			free(path);
			path = get_mini_path(env_path, &i);
		}
	}
	//path return null quand sort du while ?
	//cf access
	else if (!access(cmd, F_OK))
		path = cmd;
	return (path);
}
