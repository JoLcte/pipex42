/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/20 19:37:27 by jlecomte         ###   ########.fr       */
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
		if (data->heredoc)
			if (dup2_close(data->fds_heredoc[0], STDIN_FILENO))
				exit(EXIT_FAILURE);
		if (dup2_close(data->fd_in, STDIN_FILENO))
			exit(EXIT_FAILURE);
	}
	else if (i == data->nb_cmd - 1)
		if (dup2_close(data->fd_out, STDOUT_FILENO))
			exit(EXIT_FAILURE);
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
	int	fds[2];
	int	status;
	pid_t	pid;

	status = 0;
	data->idx = -1;
	if (pipe(fds) == -1)
		err_exit(strerror(errno), "pipe");
	while (++data->idx < data->nb_cmd)
	{
	fprintf(stderr, "coucou pipex\n");
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
		if (pipe(fds) == -1)
			err_exit(strerror(errno), "pipe");
	}
	while (data->idx--)
		waitpid(-1, &status, 0);
	return (WEXITSTATUS(status));
}

int	pipex_bonus(t_data *data, char heredoc)
{
	int	len;
	char	*line;
	int 	err;

	if (heredoc)
	{
		if (pipe(data->fds_heredoc) == -1)
			err_exit(strerror(errno), "pipe");
		len = ft_strlen(data->limiter);
		while (1)
		{
			write(1, "> ", 2); 
			err = get_next_line(0, &line);
			if (!ft_strncmp(data->limiter, line, len) || err == -1)
				break;
			write(data->fds_heredoc[1], line, ft_strlen(line));
			write(data->fds_heredoc[1], "\n", 1);
			free(line);

		}
		if (err == -1)
		{
			if (line)
				free(line);
			err_exit("get_next_line error", "heredoc");	
		}
		if (check_close(&data->fds_heredoc[0], 1))
			return (EXIT_FAILURE);
	}
	return (pipex(data));
}
