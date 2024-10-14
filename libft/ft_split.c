/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:45:06 by eaboudi           #+#    #+#             */
/*   Updated: 2024/08/27 17:30:53 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *str, char sep)
{
	size_t	i;
	size_t	words;

	if (!str)
		return (0);
	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i] != '\0')
			words++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (words);
}

static char	**ft_free_memory(char **strs, int k)
{
	while (k--)
		free(strs[k]);
	free(strs);
	return (NULL);
}

static char	**second_split(char **strs, const char *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i + j] && s[i + j] != c)
				j++;
			strs[k] = ft_substr(s + i, 0, j);
			if (!strs[k])
				return (ft_free_memory(strs, k));
			k++;
		}
		i += j;
	}
	strs[k] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	number_of_words;
	char	**strs;

	if (!s)
		return (NULL);
	number_of_words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (number_of_words + 1));
	if (!strs)
		return (NULL);
	return (second_split(strs, s, c));
}
