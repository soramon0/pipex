/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
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

int	pipe_cmds(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	cpid;
	char	**cmd_argv;
	int		fd;

	if (argc < 5)
	{
		perror("args small");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("could not init pipes");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("could not fork process");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		close(pipefd[0]);
		fd = open(argv[1], O_RDONLY, 0664);
		if (fd == -1)
		{
			perror("could not open file");
			return (-1);
		}
		if (dup2(fd, 0) == -1)
		{
			perror("could not dup file");
			return (-1);
		}
		if (dup2(pipefd[1], 1) == -1)
		{
			perror("could not dup file");
			return (-1);
		}
		cmd_argv = ft_split(argv[2], ' ');
		if (cmd_argv == NULL)
			return (-1);
		run_cmd(cmd_argv[0], cmd_argv, envp);
		ft_split_free(cmd_argv);
		close(pipefd[1]);
		close(fd);
		return (0);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("could not fork second process");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{
		fd = open(argv[4], O_WRONLY, 0664);
		if (fd == -1)
		{
			perror("could not open file");
			return (-1);
		}
		if (dup2(fd, 1) == -1)
		{
			perror("could not dup file 2");
			return (-1);
		}
		if (dup2(pipefd[0], 0) == -1)
		{
			perror("could not dup file 2");
			return (-1);
		}
		cmd_argv = ft_split(argv[3], ' ');
		if (cmd_argv == NULL)
			return (-1);
		run_cmd(cmd_argv[0], cmd_argv, envp);
		ft_split_free(cmd_argv);
		close(pipefd[0]);
		close(pipefd[1]);
		close(fd);
		return (0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	return (EXIT_SUCCESS);
}
