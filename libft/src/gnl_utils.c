/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:04:18 by jlecomte          #+#    #+#             */
/*   Updated: 2021/04/13 14:04:45 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	index_chr(char *s)
{
	char *const	save = s;

	while (*s)
	{
		if (*s == '\n')
			return (s - save);
		++s;
	}
	return (-1);
}

char	*ft_cpy(char *dst, char *src, int len)
{
	const char	*save_dst = dst;

	while (len--)
		*dst++ = *src++;
	return ((char *)save_dst);
}

char	*ft_join(char *dst, char *src, int len)
{
	char			*swp;
	const size_t	len_dst = ft_strlen(dst);

	swp = dst;
	dst = (char *)malloc(len_dst + len + 1);
	if (!dst)
	{
		free(swp);
		return (NULL);
	}
	ft_cpy(dst, swp, len_dst);
	free(swp);
	ft_cpy(dst + len_dst, src, len);
	dst[len_dst + len] = 0;
	return (dst);
}
