/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 08:24:04 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/31 18:25:21 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_mini_path(char *env)
{
	int i;

	i = 0
	while (env[i] && env[i] != ':')
		++i;
	if (env[i])
	{
		env[i] = 0;
		++i
	}
	return (i);
}

char	*get_path(char **env)
{
	char	*s; 
	int	i;

	while (*env && *env != 'P')
	      ++env;
	if (*env)
	{
		if (*env[1] == 'A')
			s = *env;
		else
			++env;
	}
	else
	{
		printf("env: PATH not found\n");
		free(data->paths);
		exit(EXIT_FAILURE);
	}
}
