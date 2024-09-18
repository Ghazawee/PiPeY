/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:52:42 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 14:51:30 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(char *cmd, char **env, int ifd, int fd[])
{
	char	**cmd_av;
	char	*cmd_path;

	if (only_space(cmd) == 1)
		inv_string(ifd, fd);
	cmd_av = ftb_split(cmd, ' ');
	cmd_path = b_get_cmd_path(cmd_av[0], env);
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

void	first_cmd(char **av, char *cmd, char **env, int fd[])
{
	int	pid;
	int	input;

	input = open(av[1], O_RDONLY, 0777);
	if (input == -1)
		input_invalid(av[1]);
	pid = fork();
	if (pid == -1)
		perror("fork fail");
	if (pid == 0)
	{
		close(fd[0]);
		if (input == -1)
		{
			close(fd[1]);
			exit(1);
		}
		execute_cmd(cmd, env, input, fd);
	}
	else
	{
		if (input != -1)
			close(input);
		close(fd[1]);
	}
}

void	middle_pipes(char *cmd, char **env, int ifd, int fd[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork fail");
	if (pid == 0)
	{
		close(fd[0]);
		execute_cmd(cmd, env, ifd, fd);
		exit(1);
	}
	else
	{
		close(ifd);
		close(fd[1]);
	}
}

void	last_cmd(int ac, char **av, char **env, int ifd)
{
	int	pid;
	int	output;

	output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
	{
		write(2, "zsh: operation not permitted: ", 30);
		ft_putendl(av[ac - 1], 2);
		close(ifd);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		perror("fork fail");
	if (pid == 0)
	{
		exe_lstcmd(av[ac - 2], env, ifd, output);
		close(ifd);
		exit(127);
	}
	else
	{
		close(ifd);
		close(output);
	}
}

void	multiple_pipes(int ac, char **av, char **env, int i)
{
	int	fd[2];
	int	pfd;
	int	status;

	if (pipe(fd) == -1)
		perror("pipe fail");
	first_cmd(av, av[2], env, fd);
	pfd = fd[0];
	while (i < ac - 2)
	{
		if (pipe(fd) == -1)
			perror("pipe fail");
		middle_pipes(av[i++], env, pfd, fd);
		close(pfd);
		close(fd[1]);
		pfd = fd[0];
	}
	last_cmd(ac, av, env, pfd);
	close(pfd);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			exit(127);
	}
}
