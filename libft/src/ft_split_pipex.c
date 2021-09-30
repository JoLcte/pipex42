/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:14:51 by jlecomte          #+#    #+#             */
/*   Updated: 2021/09/30 21:42:31 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	count_wd(char const *s, char c)
{
	int	count;
	int	tmp;

	count = 0;
	while (*s)
	{
		while (*s && *s != c)
			++s;
		count++;
		while (*s && *s == c)
			s++;
		if (*s == '\'' || *s == '"')
		{	
			count++;
			tmp = skip_quotes(s, *s);
			if (tmp == -1)
				return (-1);
			s += tmp;
		}
	}
	return (count);
}

static int	size_wd(char const *s, char c)
{
	int	len;

	len = 0;
	if (*s == '\'' || *s == '"')
	{
		c = *s;
		++s;
	}
	while (s[len] && s[len] != c)
		len++;
	if (c == '\'' || c == '"')
		return (len + 1);
	return (len);
}

static char	*get_wd(char const *s, int len_wd)
{
	char	*word;
	char	*p;

	word = (char *)malloc(len_wd + 1);
	if (!word)
		return (NULL);
	p = word;
	while (len_wd--)
		*word++ = *s++;
	*word = '\0';
	if (*(word - 1) == '\'' || *(word - 1) == '"')
		*(word - 1) = 0;
	return (p);
}

char	**ft_split_pipex(char const *s, char c)
{
	int		nb_wd;
	int		len_wd;
	char	**arr;

	while (*s && *s == c)
		++s;
	nb_wd = count_wd(s, c);
	arr = (char **)malloc(sizeof(char *) * (nb_wd + 1));
	if (nb_wd == -1 || !arr)
		return (NULL);
	while (*s)
	{
		len_wd = size_wd(s, c);
		if (*s == '\'' || *s == '"')
			++s;
		*arr++ = get_wd(s, len_wd);
		if (!*(arr - 1))
			return (free_arr(arr));
		s += len_wd;
		while (*s && *s == c)
			s++;
	}
	*arr = NULL;
	return (arr - nb_wd);
}
