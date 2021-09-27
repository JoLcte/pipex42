/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:16:35 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/27 13:16:53 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

# include "libft.h"

# ifndef BONUS
#  define BONUS 0
# endif
# ifndef BUFSIZ
#  define BUFSIZ 1024
# endif

/*
**	DATA HANDLE
*/

typedef struct s_buf
{
	char 	err[BUFSIZ];
	int 	len;
}	t_buf;

typedef struct s_data
{
	char	**cmds;
	char	**envp;
	char	*limiter;
	char	*paths;
	int	fds[2];
	int	fd_in;
	int	fd_out;
	int	nb_cmd;
	int	idx;
	char	heredoc;
}	t_data;

/*
**	PARSING FUNCTIONS
*/

char	*get_cmd_path(char *cmd, char *paths);
char 	*get_path(char **env);

/*
**	PIPE FUNCTIONS
*/

void	exe_check_err(char **cmd, char *path, char **envp);
void	exe_cmd(t_data *data, int i);
int	pipex(t_data *data);
int	pipex_bonus(t_data *data, char heredoc);

/*
**	ERROR FUNCTIONS
*/

void	err_exit(char *error, char *src, char kill_pid);

/*
**	UTILS FUNCTIONS
*/

int	check_close(int *fds, int size);
int	dup2_close(int fd_src, int fd_dst);
void	free_all(char **arr);

#endif
