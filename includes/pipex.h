/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:16:35 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/14 15:54:47 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# ifndef BUSIZ
#  define BUFSIZ 1024
# endif

/*
**	DATA HANDLE
*/

typedef struct s_buf
{
	char 	*err;
	int 	len;
}	t_buf;

typedef struct s_data
{
	char	**cmds;
	char	*paths;
	char	**envp;
	int	fd_in;
	int	fd_out;
	int	nb_cmd;
	int	idx;
}	t_data;

/*
**	PARSING FUNCTIONS
*/

char 	*get_path(char **env);
char	*get_mini_path(char *path, int *i);
char	*get_cmd_path(char *cmd, char *paths);

/*
**	PIPE FUNCTIONS
*/

void	exe_cmd(t_data *data, int i);
void	exe_check_err(char **cmd, char *path, char **envp);
int	pipex(t_data *data);
int	pipex_bonus(char **av, t_data *data);

#endif
