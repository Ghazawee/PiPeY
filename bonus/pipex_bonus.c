/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshaheen <mshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:21:28 by mshaheen          #+#    #+#             */
/*   Updated: 2024/09/18 17:27:55 by mshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	int	i;

	if (ac < 5)
	{
		write(2, "Bad Usage\n", 10);
		return (0);
	}
	if (ftb_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac == 6 && ftb_strncmp(av[1], "here_doc", 8) == 0)
			here_doc_fucn(ac, av, env);
		else
		{
			write(2, "Bad Usage\n", 10);
			exit(1);
		}
	}
	else if (ac >= 5)
	{
		i = 3;
		multiple_pipes(ac, av, env, i);
	}
	return (0);
}
