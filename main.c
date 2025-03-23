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

int	main(int argc, char *argv[], char *envp[])
{
	int	pipefd[2];
	int	in_pid;
	int	out_pid;

	in_pid = 0;
	out_pid = 0;
	if (argc != 5)
		err_exit(EXIT_FAILURE, "usage: 4 arguments required\n");
	if (pipe(pipefd) == -1)
		err_exit(EXIT_FAILURE, "pipe");
	if (process_in(argv, envp, pipefd, &in_pid) == -1)
		return (EXIT_FAILURE);
	if (process_out(argv, envp, pipefd, &out_pid) == -1)
		return (EXIT_FAILURE);
	close(pipefd[0]);
	close(pipefd[1]);
	process_wait(in_pid);
	return (process_wait(out_pid));
}
