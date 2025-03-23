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

int	is_executable(char *bin)
{
	if (access(bin, F_OK) == -1)
		return (127);
	if (access(bin, X_OK) == -1)
		return (126);
	return (0);
}

char	*ft_str_join(char *start, char *end, char join)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (start == NULL || end == NULL)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(start) + ft_strlen(end) + 2);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (start[i])
	{
		result[i] = start[i];
		i++;
	}
	result[i++] = join;
	j = 0;
	while (end[j])
		result[i++] = end[j++];
	result[i] = '\0';
	return (result);
}

char	*get_cmd_path(char *filename, char *path)
{
	char	**paths;
	char	*full_path;
	size_t	index;

	if (path == NULL || filename == NULL)
		return (NULL);
	if (ft_strlen(filename) >= 2 && filename[0] == '.' && filename[1] == '/')
		return (ft_strdup(filename));
	if (filename[0] == '/')
		return (ft_strdup(filename));
	paths = ft_split(path, ':');
	if (paths == NULL || *paths == NULL)
		return (ft_split_free(paths), NULL);
	index = 0;
	while (paths[index] != NULL)
	{
		full_path = ft_str_join(paths[index], filename, '/');
		if (full_path == NULL)
			return (ft_split_free(paths), NULL);
		if (is_executable(full_path) == 0)
			return (ft_split_free(paths), full_path);
		free(full_path);
		index++;
	}
	return (ft_split_free(paths), NULL);
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
	{
		ft_printf_fd(2, "%s:command '' not found.\n", cmd);
		return (ft_split_free(cmd_argv), 127);
	}
	bin = get_cmd_path(cmd_argv[0], path);
	if (bin == NULL)
		return (ft_split_free(cmd_argv), EXIT_FAILURE);
	status = execve(bin, cmd_argv, envp);
	perror(cmd_argv[0]);
	free(bin);
	ft_split_free(cmd_argv);
	return (status);
}
