/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:16:23 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/29 19:16:20 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_close(int *fds, int size)
{
	char	*err;
	int		len;

	while (size-- > 0)
	{
		if (close(fds[size]))
		{
			err = strerror(errno);
			len = ft_strlen(err);
			write(2, "pipex: ", 7);
			write(2, err, len);
			write(2, "\n", 1);
		}
	}
	return (0);
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	dup2_close(int fd_src, int fd_dst)
{
	dup2(fd_src, fd_dst);
	if (check_close(&fd_src, 1))
		return (EXIT_FAILURE);
	return (0);
}
