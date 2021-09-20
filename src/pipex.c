/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/20 19:25:36 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exe_check_err(char **cmd, char *path, char **envp)
{
	int ret;

	ret = 0;
	if (!path)
	{
		if (ft_strchr(*cmd, '/'))
			err_exit(strerror(errno), *cmd);
		else
			err_exit("cmd not found", *cmd);
		ret = 127;
	}
	else if (execve(path, cmd, envp) == -1)
	{
		if (!access(path, X_OK | R_OK) && open(path, O_DIRECTORY))
			ret = 0;
		else
		{
			ret = 126;
			err_exit(strerror(errno), *cmd);
		}
	}
	if (*cmd != path)
		free(path);
	free_all(cmd);
	exit(ret);
}

void	exe_cmd(t_data *data, int i)
{
	char **cmd;
	char *path;

	if (!i)
	{
		dup2(data->fd_in, STDIN_FILENO);
		if (check_close(&data->fd_in, 1))
			exit(EXIT_FAILURE);
	}
	else if (i == data->nb_cmd - 1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		if (check_close(&data->fd_out, 1))
			exit(EXIT_FAILURE);
	}
	cmd = ft_split_pipex(data->cmds[i], ' ');
	if (!cmd)
		err_exit("malloc error", "ft_split_pipex");
	if (!*cmd)
		path = 0;
	else
		path = get_cmd_path(*cmd, data->paths);
	exe_check_err(cmd, path, data->envp);
}

int	pipex(t_data *data)
{
	int fds[2];
	int status;
	pid_t pid;

	status = 0;
	data->idx = -1;
	if (pipe(fds) == -1)
		err_exit(strerror(errno), "pipe");
	while (++data->idx < data->nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			err_exit(strerror(errno), "fork");
		if (pid == 0)
		{
			dup2(fds[1], STDOUT_FILENO);
			if (check_close(&fds[0], 1))
				return (EXIT_FAILURE);
			exe_cmd(data, data->idx);
		}
		else
		{
			dup2(fds[0], STDIN_FILENO);
			if (check_close(fds, 2))
				return (EXIT_FAILURE);
		}
		//waitpid(pid, &status, 0);
		if (pipe(fds) == -1)
			err_exit(strerror(errno), "pipe");
	}
	while (data->idx--)
		waitpid(-1, &status, 0);
	return (WEXITSTATUS(status));
}

int	pipex_bonus(t_data *data, char heredoc)
{
	if (heredoc)
		printf("here is heredoc\n");
	else
		return(pipex(data));
	return (EXIT_SUCCESS);
}
