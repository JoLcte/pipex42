/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 10:16:35 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/08 14:10:45 by jlecomte         ###   ########.fr       */
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
	char	**cmds;
	char	*paths;
	int	fd_in;
	int	fd_out;
	int	nb_cmd;
	int	idx;

}	t_data;

/*
**	FUNCTIONS
*/

char 	*get_path(char **env);
int	get_mini_path(char *env);


#endif
