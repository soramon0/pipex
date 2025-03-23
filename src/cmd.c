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

int	is_executable(char *bin)
{
	if (access(bin, F_OK) == -1)
		return (127);
	if (access(bin, X_OK) == -1)
		return (126);
	return (0);
}

int	has_path(char *path)
{
	if (path == NULL)
		return (-1);
	if (path[0] == '/')
		return (0);
	if (path[0] == '.')
		return (0);
	return (-1);
}

char	*get_cmd_path(char *filename, char *envp[])
{
	char	**paths;
	char	*path;
	char	*full_path;
	size_t	index;

	if (is_executable(filename) == 0)
		return (ft_strdup(filename));
	path = ft_strsearch(envp, "PATH");
	if (path == NULL)
		return (ft_printf_fd(2, "PATH undefined\n"), NULL);
	paths = ft_split(path, ':');
	if (paths == NULL || *paths == NULL)
		return (ft_split_free(paths), NULL);
	index = 0;
	while (paths[index] != NULL)
	{
		full_path = ft_strjoin(paths[index], filename, '/');
		if (full_path == NULL)
			return (ft_split_free(paths), NULL);
		if (is_executable(full_path) == 0)
			return (ft_split_free(paths), full_path);
		free(full_path);
		index++;
	}
	return (ft_split_free(paths), ft_strdup(filename));
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_argv;
	char	*bin;

	cmd_argv = ft_split(cmd, ' ');
	if (cmd_argv == NULL)
		return (EXIT_FAILURE);
	if (cmd_argv[0] == NULL)
	{
		ft_printf_fd(2, "%s:command '' not found.\n", cmd);
		return (ft_split_free(cmd_argv), 127);
	}
	if (has_path(cmd_argv[0]) == 0 && is_executable(cmd_argv[0]) != 0)
	{
		perror(cmd_argv[0]);
		return (ft_split_free(cmd_argv), is_executable(cmd_argv[0]));
	}
	bin = get_cmd_path(cmd_argv[0], envp);
	if (bin == NULL)
		return (ft_split_free(cmd_argv), EXIT_FAILURE);
	execve(bin, cmd_argv, envp);
	perror(cmd_argv[0]);
	free(bin);
	ft_split_free(cmd_argv);
	return (EXIT_FAILURE);
}
