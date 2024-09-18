/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:16:30 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:29:06 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	ch = (char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == ch)
			return (&str[i]);
		i++;
	}
	if (str[i] == ch)
		return (&str[i]);
	return (NULL);
}

char	**find_split_path(char **env)
{
	char	*pathy;
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathy = env[i] + 5;
			break ;
		}
		i++;
	}
	paths = ft_split(pathy, ':');
	return (paths);
}

int	only_space(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
		return (1);
	while (s[i] == 32 && s[i])
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	accessible_p(char **array, char *fp)
{
	if (access(fp, X_OK) == 0)
	{
		free_array(array);
		return (1);
	}
	return (0);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*full_path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	paths = find_split_path(env);
	if (!paths)
		perror("splitting path failed\n");
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (accessible_p(paths, full_path) == 1)
			return (full_path);
		free(full_path);
	}
	free_array(paths);
	return (NULL);
}
