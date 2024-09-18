/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:08:47 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:28:57 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	last_cmd(int ac, char **av, char **env, int ifd)
{
	int	pid;
	int	output;

	output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
	{
		write(2, "zsh: operation not permitted: ", 30);
		ft_putendl_fd(av[ac - 1], 2);
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

void	pipes(int ac, char **av, char **env)
{
	int	fd[2];
	int	pfd;
	int	status;

	if (pipe(fd) == -1)
		perror("pipe fail");
	first_cmd(av, av[2], env, fd);
	pfd = fd[0];
	last_cmd(ac, av, env, pfd);
	close(pfd);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
			exit(127);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		pipes(ac, av, env);
	}
	else
		write(2, "Bad Usage\n", 10);
	return (0);
}
