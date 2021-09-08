/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:55:39 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/08 14:05:22 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_data *data, int bonus, char **av, char **envp)
{
	if (bonus && data->nb_cmd + 3 < 5)
	{
		printf("The arguments are incorrect. 
				Here is an example of how to use pipex:
				\"./pipex input_file cmd_1 cmd_2
				output_file\"\n");
		exit(EXIT_FAILURE);
	}
	else if (data->nb_cmd + 3 != 5 && !bonus)
	{	
		printf("The arguments are incorrect. Here is an example of how
				to use pipex : \"./pipex input_file cmd_1 cmd_2
				output_file\"\n");
		exit(EXIT_FAILURE);
	}
	data->fd_in = open(av[1], O_RDONLY);
	data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->paths = get_path(envp);
	data->cmds = av + 2;
	if (!data->cmds || !data->paths || data->fd_in == -1 || 
			data->fd_out == -1)
	{
		printf("pipex: could not initiate data.\n");
		exit(EXIT_FAILURE);
	}
	printf("data->paths = |%s|\n", data->paths);
	exit(EXIT_SUCCESS);
}

static int	error_init(int errno, char *cmd, char *file)
{
	const char *error = sterror(errno);
	const int fd = dup(1);

	dup2(1, 2);
	printf("%s: %s: %s\n", cmd, file, error);
	dup2(fd, 1);
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	data.idx = 0;
	data.nb_cmd = ac - 3;
	init_data(&data, BONUS, av, envp);	
	if (BONUS)
	{
		printf("BONUS\n");
		pipex_bonus(data, av, envp);
	}
	else
		pipex(data, av, envp);
	return (0);
}
