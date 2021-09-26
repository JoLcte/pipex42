/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:14:55 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/25 15:06:34 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		write(fd, "\n", 1);
	}
	if (n)
		ft_strlcpy(buf->err + buf->len, src, n);
	buf->len += n;
}

void	err_exit(char *error, char *src)
{
	t_buf buf;
	buf.len = 0;
	buf_dwrite(&buf, "pipex: ", 2);
	buf_dwrite(&buf, error, 2);
	buf_dwrite(&buf, ": ", 2);
	buf_dwrite(&buf, src, 2);
	if (buf.len)
	{
		write(2, buf.err, buf.len);
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
