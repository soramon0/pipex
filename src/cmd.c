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

char	*strs_search(char *haystack[], char *needle)
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

char	*get_cmd_path(char *filename, char *path)
{
	if (path == NULL || filename == NULL)
		return (NULL);
	if (ft_strlen(filename) >= 2 && filename[0] == '.' && filename[1] == '/')
		return (filename);
	return (filename);
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
	char	*path;
	char	*bin;
	int		status;

	path = strs_search(envp, "PATH");
	if (path == NULL)
		return (ft_printf_fd(2, "PATH undefined\n"), EXIT_FAILURE);
	cmd_argv = ft_split(cmd, ' ');
	if (cmd_argv == NULL)
		return (EXIT_FAILURE);
	if (cmd_argv[0] == NULL)
		return (ft_printf_fd(2, "%s:command '' not found.\n", cmd),
			ft_split_free(cmd_argv), 127);
	bin = get_cmd_path(cmd_argv[0], path);
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
