/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:16:35 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/30 17:36:28 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

# ifndef BONUS
#  define BONUS 0
# endif

/*
**	PARSING
*/

typedef struct s_data
{
	char **paths;
	int	fd_in;
	int	fd_out;
	int	i;
}	t_data;

/*
**	FUNCTIONS
*/

int	parse_path(char ***paths, char **env);
int	parse_cmd(char **cmds, char **av);

#endif
