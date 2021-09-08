/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 08:24:04 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/08 14:10:20 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_mini_path(char *env)
{
	int i;

	i = 0;
	while (env[i] && env[i] != ':')
		++i;
	if (env[i])
	{
		env[i] = 0;
		++i;
	}
	return (i);
}

char	*get_path(char **env)
{
	while (*env)
		if (ft_strncmp("PATH=", *env, 5))
	      		++env;
	if (*env && **env == 'P')
		return (*env + 5);
	else if (*env)
		++env;
	else
	{
		printf("env: PATH not found\n");
		exit(EXIT_FAILURE);
	}
}
