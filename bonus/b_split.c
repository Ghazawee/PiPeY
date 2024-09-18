/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:45:40 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 11:27:58 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_free(char **str, int t)
{
	int	i;

	i = 0;
	while (i <= t)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (-1);
}

int	ft_wount(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			word++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (word);
}

void	ft_strcpy(char *des, char *src, char c, int j)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c && i < j)
	{
		des[i] = src[i];
		i++;
	}
	des[i] = '\0';
}

int	ft_fill(char **str, char *s, char c, int index)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (s[i] && word < index)
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			str[word] = (char *)malloc((j + 1) * (sizeof(char)));
			if (!str[word])
				return (ft_free(str, word));
			ft_strcpy(str[word], s + i, c, j);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ftb_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_wount((char *)s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res[words] = NULL;
	if (ft_fill(res, (char *)s, c, words) == -1)
		return (NULL);
	return (res);
}
