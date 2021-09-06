/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_on_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 22:19:18 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/29 16:26:36 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_quotes(const char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c && str[i])
		++i;
	if (!str[i])
		return (-1);
	++i;
	while (str[i] == ' ')
		++i;
	return (i);
}
