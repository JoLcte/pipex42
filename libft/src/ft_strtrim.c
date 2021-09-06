/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:15:18 by jlecomte          #+#    #+#             */
/*   Updated: 2021/08/29 16:18:11 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *src, char const *set)
{
	size_t	len;
	char	*s;

	if (!src || !set)
		return (NULL);
	while (in_set(set, *src))
		++src;
	len = ft_strlen(src);
	src += (len - 1);
	if (len)
	{
		while (in_set(set, *src))
		{
			--len;
			--src;
		}
	}
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len)
		s[--len] = *src--;
	return (s);
}
