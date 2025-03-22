/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_cmd(char *pathname, char *argv[], char *envp[])
{
	if (execve(pathname, argv, envp) == -1)
	{
		perror(pathname);
		return (-1);
	}
	return (0);
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
	if (cmd_argv == NULL || cmd_argv[0] == NULL)
		return (-1);
	if (run_cmd(cmd_argv[0], cmd_argv, envp) == -1)
	{
		ft_split_free(cmd_argv);
		return (-1);
	}
	return (0);
}
