/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/30 23:12:56 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_heredoc(t_data *data)
{
	char	*line;
	int		len;
	int		err;

	if (pipe(data->fds) == -1)
		err_exit(strerror(errno), "pipe", 1);
	len = ft_strlen(data->limiter);
	while (1)
	{
		write(1, "> ", 2);
		err = get_next_line(0, &line);
		if (!ft_strncmp(data->limiter, line, len) || err == -1)
			break ;
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
	free(line);
	data->fd_in = data->fds[0];
	close(data->fds[1]);
}

/*
**	--- Execve + error return code
**	Note: if (*cmd == path) we must not free path as it is == cmd.
*/

void	exe_check_err(char **cmd, char *path, char **envp)
{
	int	ret;

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
		if (!access(path, X_OK | R_OK) && open(path, O_DIRECTORY) == -1)
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

/*
**	--- Creation of char **cmd and set up of the infile and outfile parameters
*/

void	exe_cmd(t_data *data, int i)
{
	char	**cmd;
	char	*path;

	if (!i)
	{
		if (data->fd_in == -1)
			exit(0);
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	else if (i == data->nb_cmds - 1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	cmd = ft_split_pipex(data->cmds[i], ' ');
	if (!cmd)
		err_exit("malloc error", "ft_split_pipex", 1);
	if (!*cmd)
		path = NULL;
	else
		path = get_cmd_path(*cmd, data->paths);
	exe_check_err(cmd, path, data->envp);
}

/*
**	--- Creation of pipes and forks
*/

pid_t	pipex(t_data *data)
{
	pid_t	pid;

	while (data->idx < data->nb_cmds)
	{
		if (pipe(data->fds) == -1)
			err_exit(strerror(errno), "pipe", 1);
		pid = fork();
		++data->nb_pids;
		if (pid == -1)
			err_exit(strerror(errno), "fork", 1);
		if (pid == 0)
		{
			dup2(data->fds[1], STDOUT_FILENO);
			close(data->fds[0]);
			exe_cmd(data, data->idx);
		}
		else
		{
			dup2(data->fds[0], STDIN_FILENO);
			close(data->fds[0]);
			close(data->fds[1]);
		}
		++data->idx;
	}
	return (pid);
}
