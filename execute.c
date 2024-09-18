/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:15:51 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:29:41 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *cmd, char **env, int ifd, int fd[])
{
	char	**cmd_av;
	char	*cmd_path;

	if (only_space(cmd) == 1)
		inv_string(ifd, fd);
	cmd_av = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(cmd_av[0], env);
	if (!cmd_path)
		inv_cmd(cmd_av[0], cmd_av, ifd, fd);
	if (ifd != STDIN_FILENO)
	{
		dup2(ifd, STDIN_FILENO);
		close(ifd);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (execve(cmd_path, cmd_av, env) == -1)
		inv_cmd(cmd_av[0], cmd_av, ifd, fd);
}

void	exe_lstcmd(char *cmd, char **env, int ifd, int ofd)
{
	char	**cmd_av;
	char	*cmd_path;

	if (only_space(cmd) == 1)
		inv_last_string(ifd, ofd);
	cmd_av = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(cmd_av[0], env);
	if (!cmd_path)
		invlstcmd(cmd_av[0], cmd_av, ifd, ofd);
	if (ifd != STDIN_FILENO)
	{
		dup2(ifd, STDIN_FILENO);
		close(ifd);
	}
	if (ofd != STDOUT_FILENO)
	{
		dup2(ofd, STDOUT_FILENO);
		close(ofd);
	}
	if (execve(cmd_path, cmd_av, env) == -1)
		invalid_lstcmd(cmd_av[0], cmd_av, ifd);
}
