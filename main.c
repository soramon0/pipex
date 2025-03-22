/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/pipex.h"

int	group_wait(int in_pid, int out_pid, int *in_status, int *out_status)
{
	waitpid(in_pid, in_status, 0);
	waitpid(out_pid, out_status, 0);
	if (!WIFEXITED(*in_status) || WEXITSTATUS(*in_status) != 0
		|| !WIFEXITED(*out_status) || WEXITSTATUS(*out_status) != 0)
		return (-1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	pipefd[2];
	int	in_status;
	int	out_status;
	int	*in_pid;
	int	*out_pid;

	in_pid = NULL;
	out_pid = NULL;
	if (argc < 5)
		err_exit(EXIT_FAILURE, "usage: minimum 4 arguments\n");
	if (pipe(pipefd) == -1)
		err_exit(EXIT_FAILURE, "pipe");
	if (process_in(argv, envp, pipefd, in_pid) == -1)
		return (EXIT_FAILURE);
	if (process_out(argv, envp, pipefd, out_pid) == -1)
		return (EXIT_FAILURE);
	close(pipefd[0]);
	close(pipefd[1]);
	group_wait(*in_pid, *out_pid, &in_status, &out_status);
	return (EXIT_SUCCESS);
}
