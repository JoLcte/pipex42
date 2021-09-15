/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:05:04 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/15 21:01:04 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, char c)
{
	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (*s != c && *s)
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
