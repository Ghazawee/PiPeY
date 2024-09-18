/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:39:08 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 13:58:06 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	inv_last_string(int ifd, int ofd)
{
	write(2, "invalid string\n", 15);
	close(ifd);
	close(ofd);
	exit(127);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_putstr(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ns;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ftb_strlen(s))
		ns = 0;
	if (len > (unsigned int)ftb_strlen(s) - start)
		len = (unsigned int)ftb_strlen(s) - start;
	ns = malloc(sizeof(*s) * (len + 1));
	if (!ns)
		return (NULL);
	while (i < len && s[start + i])
	{
		ns[i] = s[start + i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
