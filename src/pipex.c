/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/09 18:11:58 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_close(int *fds, int n)
{
	char *err;
	int len_err;

	while (n--)
	{
		if (close(fds[n]))
		{
			err = strerror(errno);
			len_err = ft_strlen(err);
			write(2, err, len_err);
			exit(EXIT_FAILURE);
		}
	}
}

static void	buf_dwrite(t_buf *buf, char *src, int fd)
{
	int n;
	int free_space;

	n = ft_strlen(src);	
	free_space = BUFSIZ - buf->len;
	while (n > free_space)
	{
		ft_strlcpy(buf->err + buf->len, src, free_space);
		buf->len = 0;
		n -= free_space;
		src += free_space;
		free_space = BUFSIZ;
		write(fd, buf->err, BUFSIZ);
	}
	if (n)
		ft_strlcpy(buf->err + buf->len, src, n);
	buf->len += n;
}

static void	err_exit(char *error, char *src)
{
	t_buf buf;

	buf.len = 0;
	buf_dwrite(&buf, "pipex: ", 2);
	buf_dwrite(&buf, error, 2);
	buf_dwrite(&buf, ": ", 2);
	buf_dwrite(&buf, src, 2);
	exit(EXIT_FAILURE);
}

int	pipex(t_data *data)
{
	int fds[2];
	int status;
	pid_t new_pid;

	status = 0;
	data->idx = -1;
	if (pipe(fds) == -1)
		err_exit(strerror(errno), "pipe");
	while (++data->idx < data->nb_cmd)
	{
		new_pid = fork();
		if (new_pid == -1)
			err_exit(strerror(errno), "fork");
		if (!new_pid)
		{
			dup2(fds[0], STDIN_FILENO);
			check_close(&fds[1], 1);
			exe_cmd(data, data->idx);
		}
		waitpid(new_pid, &status, 0);
	}
	check_close(fds, 2);
	return (WEXITSTATUS(status));
	//ON EN EST LA!!!!
}

int	pipex_bonus(char **av, t_data *data)
{
	(void)av;
	(void)data;
	printf("We\'re in Bonus ! It worked ! BONUUUUUUS\n");
	return (EXIT_SUCCESS);
}

void	exe_cmd(t_data *data, int i)
{
	char **cmd;
	char *path;

	if (!i)
	{
		dup2(data->fd_in, STDIN_FILENO);
		check_close(&data->fd_in, 1);
	}
	else if (i == data->nb_cmd - 1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		check_close(&data->fd_out, 1);
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
		if (!access(path, X_OK | R_OK) && !is_directory(path))
			ret = 0;
		else
		{
			ret = 126;
			err_exit(strerror(errno), *cmd);
		}
	}
	//COMPRENDRE WHY
	if (*cmd != path)
		free(path);
	free_all(cmd);
	// A CODER
	exit(ret);
}
