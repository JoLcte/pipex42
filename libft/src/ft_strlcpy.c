/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:05:46 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/08 14:45:51 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*p_start = src;

	if (!dst || !src)
		return (0);
	while ((size > 1) && *src)
	{
		*dst++ = *src++;
		size--;
	}
	if (size != 0)
		*dst = '\0';
	while (*src)
		src++;
	return ((size_t)(src - p_start));
}
