/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guard_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:28:00 by sangmlee          #+#    #+#             */
/*   Updated: 2022/07/01 14:34:21 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	guard_execve(char *file, char **argv, char **envp)
{
	if (!file)
		exit_error("Command not found", 127);
	if (execve(file, argv, envp) == -1)
		exit_error("execve failed", ERROR_EXIT);
}

void	guard_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_error("dup2 fail", ERROR_EXIT);
}

void	guard_close(int fd)
{
	if (close(fd) == -1)
		exit_error("close fail", ERROR_EXIT);
}

int	guard_open(const char *file, int flag, int mode)
{
	int	fd;

	if (mode == EMPTY_MODE)
		fd = open(file, flag);
	else
		fd = open(file, flag, mode);
	if (fd == -1)
		exit_error("open fail", ERROR_EXIT);
	return (fd);
}
