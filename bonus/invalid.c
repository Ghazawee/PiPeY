/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:43:16 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 13:58:24 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	inv_string(int ifd, int fd[])
{
	write(2, "invalid string\n", 15);
	close(ifd);
	close(fd[1]);
	close(fd[0]);
	exit(1);
}

void	input_invalid(char *file)
{
	write(2, "zsh: no such file or directory: ", 32);
	ft_putendl(file, 2);
}

void	inv_cmd(char *cmd, char **array, int ifd, int fd[])
{
	write(2, "zsh: command not found: ", 24);
	ft_putendl(cmd, 2);
	free_array(array);
	close(ifd);
	close(fd[1]);
	close(fd[0]);
	exit(1);
}

void	invlstcmd(char *cmd, char **array, int ifd, int ofd)
{
	write(2, "zsh: command not found: ", 24);
	ft_putendl(cmd, 2);
	free_array(array);
	close(ifd);
	close(ofd);
	exit(127);
}

void	invalid_lstcmd(char *cmd, char **array, int ifd)
{
	write(2, "zsh: command not found: ", 24);
	ft_putendl(cmd, 2);
	free_array(array);
	close(ifd);
	exit(127);
}
