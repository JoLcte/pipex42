/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/27 20:12:56 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exe_check_err(char **cmd, char *path, char **envp)
{
	int ret;

	ret = 0;
	if (!path)
	{
		if (ft_strchr(*cmd, '/'))
			err_exit(strerror(errno), *cmd, 0);
		else
			err_exit("command not found", *cmd, 0);
		ret = 127;
	}
	else if (execve(path, cmd, envp) == -1)
	{
		if (!access(path, X_OK | R_OK) && open(path, O_DIRECTORY))
			ret = 0;
		else
		{
			err_exit(strerror(errno), *cmd, 0);
			ret = 126;
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
		if (dup2_close(data->fd_in, STDIN_FILENO))
			exit(EXIT_FAILURE);
	}
	else if (i == data->nb_cmd - 1)
		if (dup2_close(data->fd_out, STDOUT_FILENO))
			exit(EXIT_FAILURE);
	cmd = ft_split_pipex(data->cmds[i], ' ');
	if (!cmd)
		err_exit("malloc error", "ft_split_pipex", 1);
	if (!*cmd)
		path = 0;
	else
		path = get_cmd_path(*cmd, data->paths);
	exe_check_err(cmd, path, data->envp);
}

int	pipex(t_data *data)
{
	pid_t	pid;
	int	status;
	int	nb_pids;
	int	ret;

	status = 0;
	nb_pids = 0;
	if (pipe(data->fds) == -1)
		err_exit(strerror(errno), "pipe", 1);
	while (++data->idx < data->nb_cmd)
	{
		pid = fork();
		++nb_pids;
		if (pid == -1)
			err_exit(strerror(errno), "fork", 1);
		if (pid == 0)
		{
			dup2(data->fds[1], STDOUT_FILENO);
			if (check_close(&data->fds[0], 1))
				return (0);
			exe_cmd(data, data->idx);
		}
		else
		{

			dup2(data->fds[0], STDIN_FILENO);
			if (check_close(data->fds, 2))
				return (0);
		}
		if (pipe(data->fds) == -1)
			err_exit(strerror(errno), "pipe", 1);	
	}
	fprintf(stderr, "nb_pids = %d\n", nb_pids);
	while (nb_pids--)
	{
		printf("hello\n");
		if (waitpid(-1, &status, 0) == pid)
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	pipex_bonus(t_data *data, char heredoc)
{
	int	len;
	char	*line;
	int 	err;

	if (heredoc)
	{
		if (pipe(data->fds) == -1)
			err_exit(strerror(errno), "pipe", 1);
		len = ft_strlen(data->limiter);
		while (1)
		{
			write(1, "> ", 2); 
			err = get_next_line(0, &line);
			if (!ft_strncmp(data->limiter, line, len) || err == -1)
				break;
			write(data->fds[1], line, ft_strlen(line));
			write(data->fds[1], "\n", 1);
			free(line);
		}
		if (err == -1)
		{
			if (line)
				free(line);
			err_exit("get_next_line error", "heredoc", 1);	
		}
		data->fd_in = data->fds[0];
		if (check_close(&data->fds[1], 1))
			return (0);
	}
	return (pipex(data));
}
