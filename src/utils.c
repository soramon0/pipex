/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/11/05 14:07:37 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_exit(int status, char *fmt, ...)
{
	va_list	args;

	if (fmt != NULL)
	{
		va_start(args, fmt);
		ft_vprintf_fd(args, STDERR_FILENO, fmt);
		va_end(args);
	}
	exit(status);
}

int	process_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
