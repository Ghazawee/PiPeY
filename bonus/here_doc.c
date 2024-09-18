/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 11:04:26 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 13:57:49 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exe_lstcmd(char *cmd, char **env, int ifd, int ofd)
{
	char	**cmd_av;
	char	*cmd_path;

	if (only_space(cmd) == 1)
		inv_last_string(ifd, ofd);
	cmd_av = ftb_split(cmd, ' ');
	cmd_path = b_get_cmd_path(cmd_av[0], env);
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

void	read_write_delimiter(char **av, int pipefd[])
{
	char	*line;
	char	*limiter;

	limiter = ftb_strjoin(av[2], "\n");
	if (!limiter)
		return ;
	while (1)
	{
		line = get_next_line(0);
		if (ftb_strncmp(limiter, line, ftb_strlen(limiter)) == 0)
		{
			free(limiter);
			free(line);
			close(pipefd[1]);
			return ;
		}
		ft_putstr(line, pipefd[1]);
		free(line);
	}
	free(limiter);
	close(pipefd[1]);
	return ;
}

void	hd_last_cmd(int ac, char **av, char **env, int ifd)
{
	int	pid;
	int	outfd;

	outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfd == -1)
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
		exe_lstcmd(av[ac - 2], env, ifd, outfd);
	}
	else
	{
		close(ifd);
		if (outfd != -1)
			close(outfd);
	}
}

void	hd_multiple_pipes(int ac, char **av, char **env, int pfd)
{
	int	fd[2];
	int	i;
	int	wstatus;

	i = 3;
	while (i < ac - 2)
	{
		if (pipe(fd) == -1)
			perror("pipe fail");
		middle_pipes(av[i++], env, pfd, fd);
		close(pfd);
		close(fd[1]);
		pfd = fd[0];
	}
	wait(NULL);
	hd_last_cmd(ac, av, env, pfd);
	close(pfd);
	while (wait(&wstatus) > 0)
	{
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 127)
			exit(127);
	}
}

void	here_doc_fucn(int ac, char **av, char **env)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		perror("pipe");
	read_write_delimiter(av, pipefd);
	close(pipefd[1]);
	hd_multiple_pipes(ac, av, env, pipefd[0]);
	close(pipefd[0]);
}
