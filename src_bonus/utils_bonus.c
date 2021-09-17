/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:16:23 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/17 21:17:47 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_close(int *fds, int size)
{
	char *err;
	int len_err;

	while (size--)
	{
		if (close(fds[size]))
		{
			err = strerror(errno);
			len_err = ft_strlen(err);
			write(2, err, len_err);
			write(2, "\n", 1);
			return(EXIT_FAILURE);
		}
	}
	return (0);
}

void	free_all(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
