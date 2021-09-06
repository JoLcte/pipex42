/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/31 18:24:52 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	error_pipe(const char *cmd, const char *file, int errno)
{
	const char *error = sterror(errno);
	const int	fd = dup(1);
	
	dup2(1, 2);
	printf("%s: %s: %s\n", cmd, file, error);
	dup2(fd, 1);
	return (EXIT_FAILURE);
}

int	pipex(t_data *data, char **av, char **envp)
{
	int fds[2];
	int status;
	t_pid child1;
	t_pid child2;

	data->path = get_path(envp);
	status = 0;
	pipe(fds);
	child1 = fork();
	if (child1 < 0)
		return (error_pipe( "Fork", "...?"));
	if (!child1)
		child_one(data, av[2], envp);
	child2 = fork();
	if (child2 < 0)
		return (error_pipe(1, "Fork", "...?"));
	if (!child2)
		child_two(data, av, envp);
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
	return (EXIT_SUCCESS);
}

int	pipex_bonus(char **av, t_data *data)
{
	(void)av;
	(void)data;
	return (EXIT_SUCCESS);
}

int	child_one(t_data *data, char **av, char **envp)
{
	int i;

	i = 0;
	data->cmd = ft_split_pipex(av[data->i], ' ');
	++data->i;
	while (*data->paths)
	{
		i = get_mini_path(data->paths);
		execve(data->paths, cmd, envp);
		error_exec(data, strerror(1));
		free(cmd);
		data->paths += i;
	}
	return (EXIT_SUCCESS);
}
