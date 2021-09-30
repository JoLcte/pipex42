/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 14:55:39 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/29 16:02:19 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_error(t_data *data, int ac, int bonus)
{
	if (data->heredoc && ac < 6)
	{
		write(2, "pipex: incorrect arguments\nnote: \'./pipex", 42);
		write(2, " here_doc LIMITER cmd_1 ... cmd_n file\'\n", 40);
		exit(EXIT_FAILURE);
	}
	else if (bonus && ac < 5)
	{
		write(2, "pipex: incorrect arguments\nnote : \'./pipex", 42);
		write(2, " input_file cmd_1 ... cmd_n output_file\'\n", 41);
		exit(EXIT_FAILURE);
	}
	else if (ac != 5 && !bonus)
	{	
		write(2, "pipex: incorrect arguments\nnote: \'./pipex", 42);
		write(2, " input_file cmd_1 cmd_2 output_file\'\n", 37);
		exit(EXIT_FAILURE);
	}
}

static void	init_data(t_data *data, int bonus, int ac, char **av)
{
	data->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT |
			(O_TRUNC * !data->heredoc) | (O_APPEND * data->heredoc), 0644);
	data->cmds = av + 2 + data->heredoc;
	data->nb_cmd = ac - 3 - data->heredoc;
	data->paths = get_path(data->envp);
	if (bonus && data->heredoc)
	{
		data->limiter = av[2];
		data->fd_in = 0;
	}
	else
	{
		data->limiter = 0;
		data->fd_in = open(av[1], O_RDONLY);
	}
	if (data->fd_in == -1)
		err_exit(strerror(errno), av[1], 0);
	if (data->fd_out == -1)
	{
		--data->nb_cmd;
		err_exit(strerror(errno), av[ac - 1], 0);
	}
	if (!data->cmds || !data->paths || !data->envp)
		err_exit("Data pointers could not be referenced", "init_data", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		ret;

	if (BONUS && ac > 1)
		data.heredoc = (ft_strncmp("here_doc", av[1], 8) == 0);
	else
		data.heredoc = 0;
	check_error(&data, ac, BONUS);
	data.envp = envp;
	data.idx = -1;
	init_data(&data, BONUS, ac, av);
	if (BONUS)
	{
		ret = (pipex_bonus(&data, data.heredoc));
		if (data.heredoc)
			close(data.fds[0]);
	}
	else
		ret = (pipex(&data));
	return (ret);
}
