/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:22:14 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/08 15:54:49 by jlecomte         ###   ########.fr       */
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

static int	buf_dwrite(t_buf *buf, char *src, int fd)
{
	int n;
	int free_len;

	n = ft_strlen(src);	
	free_len = BUFSIZ - buf->len;
	while (n > free_len)
	{
		ft_cpy(buf->err + buf->len, src, free_len);
		buf->len = 0;
		n -= free_len;
		src += free_len;
		free_len = BUFSIZ;
		write(fd, buf->err, BUFSIZ);
	}
	if (n)
		ft_strlcpy(buf->err + buf->len, src, n);
	buf->len += n;
}

static void	err_exit(char *error, char *src, int *fds)
{
	t_buf buf;

	buf.len = 0;
	buf_dwrite(&buf, "pipex: ", 2);
	buf_dwrite(&buf, error, 2);
	buf_dwrite(&buf, ": ", 2);
	buf_dwrite(&buf, src, 2);
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
	exit(EXIT_FAILURE);
}

int	pipex(t_data *data, char **av, char **envp)
{
	int fds[2];
	int status;
	pid_t new_pid;

	status = 0;
	data->idx = 0;
	if (pipe(fds) == -1)
		eixt_err(strerror(errno), "pipe", fds);
	while (data->idx < data->nb_cmd)
	{
		new_pid = fork();
		if (new_pid == -1)
			exit_err(strerror(errno), "fork", fds);
		if (!new_pid)
		{
			dup2(fds[0], stdin);
			close(fds[1]);
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
