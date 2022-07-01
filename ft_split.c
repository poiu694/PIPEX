/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangmlee <sangmlee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:20:57 by sangmlee          #+#    #+#             */
/*   Updated: 2022/07/01 14:16:24 by sangmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_get_token_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	if (s == NULL)
		return (cnt);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s != c)
		{
			cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static void	ft_free_array(char **ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
}

char	*ft_get_token(char **array, char *s_temp, char const *s)
{
	char	*ret;

	if (s_temp == 0)
		ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		ret = (char *)malloc(sizeof(char) * (s_temp - s + 1));
	if (ret == NULL)
	{
		ft_free_array(array);
		return (NULL);
	}
	if (s_temp == 0)
		ft_strlcpy(ret, s, (ft_strlen(s) + 1));
	else
		ft_strlcpy(ret, s, (s_temp - s + 1));
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	size;
	char	**ret;
	char	*s_temp;

	if (s == NULL)
		return (NULL);
	size = ft_get_token_cnt(s, c);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		s_temp = ft_strchr(s, (int)c);
		ret[i] = ft_get_token(ret, s_temp, s);
		s = s_temp + 1;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
