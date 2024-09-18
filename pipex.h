/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:19:27 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:28:05 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		only_space(char *s);
int		accessible_p(char **array, char *fp);
char	**find_split_path(char **env);
char	*get_cmd_path(char *cmd, char **env);

void	inv_last_string(int ifd, int ofd);
void	free_array(char **array);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

void	inv_string(int ifd, int fd[]);
void	inv_cmd(char *cmd, char **array, int ifd, int fd[]);
void	invalid_lstcmd(char *cmd, char **array, int ifd);
void	invlstcmd(char *cmd, char **array, int ifd, int ofd);
void	input_invalid(char *file);

void	execute_cmd(char *cmd, char **env, int ifd, int fd[]);
void	exe_lstcmd(char *cmd, char **env, int ifd, int ofd);
char	*ft_strchr(const char *s, int c);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);

#endif