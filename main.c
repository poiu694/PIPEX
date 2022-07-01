/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:02:02 by sangmlee          #+#    #+#             */
/*   Updated: 2022/07/01 14:58:14 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **array)
{
	int	idx;

	idx = 0;
	while (array[idx])
	{
		free(array[idx]);
		array[idx] = NULL;
		idx++;
	}
	free(array);
	array = NULL;
}

static char	**find_path(char **envp)
{
	int		idx;
	char	**path;

	idx = 0;
	path = NULL;
	while (envp[idx++])
	{
		if (ft_strncmp(envp[idx], "PATH=", 5) == 0)
		{
			path = ft_split((envp[idx] + 5), ':');
			return (path);
		}
	}
	free_array(path);
	exit_error("PATH not FOUND", 127);
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	int		idx;
	char	*cmd_path;
	char	*temp_cmd;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	idx = 0;
	while (paths && paths[idx++])
	{
		temp_cmd = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(paths[idx], temp_cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(temp_cmd);
			return (cmd_path);
		}
		free(temp_cmd);
		free(cmd_path);
	}
	return (NULL);
}

static void	init_node(t_node *node, char *file, char *cmd, char **envp)
{
	char	**paths;

	paths = find_path(envp);
	node->file = file;
	node->exec_argv_cmd = ft_split(cmd, ' ');
	node->exec_file_path = get_cmd_path(node->exec_argv_cmd[0], paths);
	free_array(paths);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_node	node1;
	t_node	node2;

	if (argc == 5)
	{
		init_node(&node1, argv[1], argv[2], envp);
		init_node(&node2, argv[4], argv[3], envp);
		node1.next = &node2;
		node2.next = NULL;
		pipex_logic(&node1);
		while (wait((int *)0) != -1)
			;
	}
}
