/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:31:20 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:10:36 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**findsplit_path(char **env)
{
	char	*pathy;
	char	**paths;
	int		i;

	i = 0;
	pathy = NULL;
	while (env[i])
	{
		if (ftb_strncmp(env[i], "PATH=", 5) == 0)
		{
			pathy = env[i] + 5;
			break ;
		}
		i++;
	}
	paths = ftb_split(pathy, ':');
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

char	*b_get_cmd_path(char *cmd, char **env)
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
	paths = findsplit_path(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		tmp = ftb_strjoin(paths[i++], "/");
		full_path = ftb_strjoin(tmp, cmd);
		free(tmp);
		if (accessible_p(paths, full_path) == 1)
			return (full_path);
		free(full_path);
	}
	free_array(paths);
	return (NULL);
}
