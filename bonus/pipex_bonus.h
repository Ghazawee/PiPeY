/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:21:42 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:32:12 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// invalid
void	inv_string(int ifd, int fd[]);
void	inv_cmd(char *cmd, char **array, int ifd, int fd[]);
void	invalid_lstcmd(char *cmd, char **array, int ifd);
void	invlstcmd(char *cmd, char **array, int ifd, int ofd);
void	input_invalid(char *file);

// free_write
void	inv_last_string(int ifd, int ofd);
void	free_array(char **array);
void	ft_putendl(char *s, int fd);
void	ft_putstr(char *s, int fd);
char	*ft_substr(char *s, unsigned int start, size_t len);

// get path ../pipe_utils
char	**findsplit_path(char **env);
int		only_space(char *s);
int		accessible_p(char **array, char *fp);
char	*b_get_cmd_path(char *cmd, char **env);

// here_doc
void	read_write_delimiter(char **av, int pipefd[]);
void	hd_multiple_pipes(int ac, char **av, char **env, int pfd);
void	hd_last_cmd(int ac, char **av, char **env, int ifd);
void	here_doc_fucn(int ac, char **av, char **env);
void	exe_lstcmd(char *cmd, char **env, int ifd, int ofd);

// gnl
char	*get_next_line(int fd);
char	*ft_readline(int fd, char *buff, char *str);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);

// multiple_pipes
void	execute_cmd(char *cmd, char **env, int ifd, int fd[]);
void	first_cmd(char **av, char *cmd, char **env, int fd[]);
void	multiple_pipes(int ac, char **av, char **env, int i);
void	middle_pipes(char *cmd, char **env, int ifd, int fd[]);
void	last_cmd(int ac, char **av, char **env, int ifd);

// str manipulation
char	**ftb_split(char const *s, char c);
char	*ftb_strjoin(char const *s1, char const *s2);
int		ftb_strlen(const char *s);
int		ftb_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);

#endif