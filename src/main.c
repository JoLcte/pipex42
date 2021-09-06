/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:55:39 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/31 16:58:29 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int error_check(int ac, int bonus)
{
	if (bonus && ac == 5)
	{
		printf("BAAAD\n");
		return (1);
	}
	return (0);
}

static int	error_init(int errno, char *cmd, char *file)
{
	const char *error = sterror(errno);
	const int fd = dup(1);
	
	dup2(1, 2);
	printf("%s: %s: %s\n", cmd, file, error);
	dup2(fd, 1);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	data.cmd = 0;
	data.paths = 0;
	data.i = 0;
	if (error_check(ac, BONUS))
		return (0);
	data.fd_in = open(av[1], O_RDONLY);
	data.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data.fd_in < 0)
		return (error_init(EACCES, av[2], av[1]));
	if (data.fd_out < 0)
		return (error_init(EACCES, av[ac - 2], av[ac -1]));
	if (BONUS)
	{
		printf("BONUS\n");
		pipex_bonus(data, av, envp);
	}
	else
		pipex(data, av, envp);
	return (0);
}
