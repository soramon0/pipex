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

char *strs_search(char *haystack[], char *needle)
{
	int	i;
	int	n;

	if (haystack == NULL || needle == NULL)
		return (NULL);
	n = ft_strlen(needle);
	i = 0;
	while (haystack[i] != NULL)
	{
		if (ft_strncmp(haystack[i], needle, n) == 0)
			return (haystack[i]);
		i++;
	}
	return (NULL);
}

char *get_binpath(char *filename, char *path)
{
	if (path == NULL || filename == NULL)
		return (NULL);
	ft_printf_fd(2, path);
	return (NULL);
}

int	run_cmd(char *bin, char *argv[], char *envp[])
{
	if (access(bin, F_OK) == -1)
		return (127);
	if (access(bin, X_OK) == -1)
		return (126);
	return (execve(bin, argv, envp));
}

int	exec_cmd(char *cmd, char *envp[])
{
	char	**cmd_argv;
	int		status;
	char	*path;
	char	*bin;

	path = strs_search(envp, "PATHS");
	if (path == NULL)
		return (ft_printf_fd(2, "PATH undefined\n"), EXIT_FAILURE);
	cmd_argv = ft_split(cmd, ' ');
	if (cmd_argv == NULL || cmd_argv[0] == NULL)
		return (ft_split_free(cmd_argv), EXIT_FAILURE);
	bin = get_binpath(cmd_argv[0], path);
	if (bin == NULL)
		return (ft_split_free(cmd_argv), EXIT_FAILURE);
	status = run_cmd(bin, cmd_argv, envp);
	if (status != 0)
	{
		perror(cmd_argv[0]);
		ft_split_free(cmd_argv);
	}
	return (status);
}
