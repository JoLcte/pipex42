/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:55:39 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/20 19:32:43 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_error(t_data *data, int ac, int bonus)
{
	if (bonus && ac < 5)
	{
		printf("pipex: incorrect arguments\nnote: \'
			./pipex input_file cmd_1 ... cmd_n output_file\'\n");
		exit(EXIT_FAILURE);
	}
	else if (ac != 5 && !bonus)
	{	
		printf("pipex: incorrect arguments\nnote: \'
			./pipex input_file cmd_1 cmd_2 output_file\'\n");
		exit(EXIT_FAILURE);
	}
	else if (data->heredoc && ac < 6)
	{
		printf("pipex: incorrect arguments\nnote: \'
			./pipex here_doc LIMITER cmd_1 ... cmd_n file\'\n");
		exit(EXIT_FAILURE);
	}
}

static void	init_data(t_data *data, int bonus, int ac, char **av)
{
	if (bonus && ft_strncmp("here_doc", av[1], 8))
	{
		data->heredoc = 1;
		data->limiter = av[1];
		data->fd_in = 0;
	}
	else
	{
		data->heredoc = 0;
		data->limiter = 0;
		data->fd_in = open(av[1], O_RDONLY);
	}
	check_error(data, ac, bonus);
	data.fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->paths = get_path(envp);
	data->cmds = av + 2;
	if (!data->fd_in == -1 || data->fd_out == -1 ||
		!data->cmds || !data->paths || !data->envp)
	{
		printf("pipex: could not initiate data.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data data;

	data.idx = 0;
	data.nb_cmd = ac - 3;
	data.envp = envp;
	init_bonus(&data, BONUS, ac, av);	
	if (BONUS)
		return (pipex_bonus(&data, data.heredoc));
	else
		return (pipex(&data));
}