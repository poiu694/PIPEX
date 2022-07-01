/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:02:56 by sangmlee          #+#    #+#             */
/*   Updated: 2022/07/01 14:30:32 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define EMPTY_MODE	-1
# define ERROR_EXIT	1
# define SUCCESS_EXIT 0
# define FIRST_CHILD 1
# define LAST_CHILD 2

typedef struct s_node
{
	char			*file;
	char			**exec_argv_cmd;
	char			*exec_file_path;
	struct s_node	*next;
}	t_node;

void	pipex_logic(t_node *root);
void	exit_error(const char *msg, int code);
void	guard_dup2(int fd1, int fd2);
void	guard_close(int fd);
void	guard_write(int fd, const char *buf, size_t size);
int		guard_open(const char *file, int flag, int mode);
void	guard_execve(char *file, char **argv, char **envp);

char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
