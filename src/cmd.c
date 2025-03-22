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
	if (access(pathname, F_OK) == -1)
		return (127);
	if (access(pathname, X_OK) == -1)
		return (126);
	return (execve(pathname, argv, envp));
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_argv;
	int		status;

	cmd_argv = ft_split(cmd, ' ');
	if (cmd_argv == NULL || cmd_argv[0] == NULL)
		return (ft_split_free(cmd_argv), EXIT_FAILURE);
	status = run_cmd(cmd_argv[0], cmd_argv, envp);
	if (status != 0)
	{
		perror(cmd_argv[0]);
		ft_split_free(cmd_argv);
	}
	return (status);
}
