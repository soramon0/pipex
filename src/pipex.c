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

int	channel(int src, int dest)
{
	if (src == dest)
	{
		ft_putstr_fd("In/Out same file descriptor", 2);
		return (-1);
	}
	if (dup2(src, dest) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

int	redirect_input_to_pipe(char *filename, int flags, int pipefd[2])
{
	int	fd;

	close(pipefd[0]);
	fd = open(filename, flags, 0664);
	if (fd == -1)
	{
		close(pipefd[1]);
		perror(filename);
		return (-1);
	}
	if (channel(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		close(pipefd[1]);
		return (-1);
	}
	if (channel(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(fd);
		close(pipefd[1]);
		return (-1);
	}
	return (fd);
}

int	redirect_pipe_to_output(char *filename, int flags, int pipefd[2])
{
	int	fd;

	close(pipefd[1]);
	fd = open(filename, flags, 0664);
	if (fd == -1)
	{
		close(pipefd[0]);
		perror(filename);
		return (-1);
	}
	if (channel(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		close(pipefd[0]);
		return (-1);
	}
	if (channel(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		close(fd);
		return (-1);
	}
	return (fd);
}

int	process_in(char *argv[], char *envp[], int pipefd[2], int *pid)
{
	int	fd;
	int	pid_fallback;

	pid_fallback = 0;
	if (pid == NULL)
		pid = &pid_fallback;
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (*pid != 0)
		return (0);
	fd = redirect_input_to_pipe(argv[1], O_RDONLY, pipefd);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (exec_cmd(argv[2], envp) == -1)
	{
		close(pipefd[1]);
		close(fd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	process_out(char *argv[], char *envp[], int pipefd[2], int *pid)
{
	int	fd;
	int	pid_fallback;

	pid_fallback = 0;
	if (pid == NULL)
		pid = &pid_fallback;
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (*pid != 0)
		return (0);
	fd = redirect_pipe_to_output(argv[4], O_WRONLY | O_CREAT | O_TRUNC, pipefd);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (exec_cmd(argv[3], envp) == -1)
	{
		close(pipefd[0]);
		close(fd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
