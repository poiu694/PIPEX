/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:17:53 by sangmlee          #+#    #+#             */
/*   Updated: 2022/07/01 14:40:24 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	process_first_child(t_node *node, int *fd)
{
	int	file_fd;

	guard_close(fd[0]);
	file_fd = guard_open(node->file, O_RDONLY, EMPTY_MODE);
	guard_dup2(file_fd, 0);
	guard_dup2(fd[1], 1);
	guard_execve(node->exec_file_path, node->exec_argv_cmd, NULL);
}

static void	process_last_child(t_node *node, int *fd)
{
	int	file_fd;

	guard_close(fd[1]);
	file_fd = guard_open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	guard_dup2(file_fd, 1);
	guard_dup2(fd[0], 0);
	guard_execve(node->exec_file_path, node->exec_argv_cmd, NULL);
}

static void	process_child_image(t_node *node, int *fd, int child_idx)
{
	if (child_idx == FIRST_CHILD)
		process_first_child(node, fd);
	else if (child_idx == LAST_CHILD)
		process_last_child(node, fd);
	exit(SUCCESS_EXIT);
}

static void	process_parent_image(int *fd, int idx)
{
	if (idx > 1)
	{
		guard_close(fd[0]);
		guard_close(fd[1]);
	}
}

void	pipex_logic(t_node *node)
{
	int		fd[2];
	int		idx;
	pid_t	pid;
	t_node	*temp_node;

	if (pipe(fd) == -1)
		exit_error("pipe fail", ERROR_EXIT);
	temp_node = node;
	idx = 1;
	while (1)
	{
		pid = fork();
		if (pid == -1)
			exit_error("fork error", ERROR_EXIT);
		else if (pid == 0)
			process_child_image(temp_node, fd, idx);
		else
		{
			if (temp_node->next == NULL)
				break ;
			temp_node = temp_node->next;
			idx++;
		}
	}
	process_parent_image(fd, idx);
}
