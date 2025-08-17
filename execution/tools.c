/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:10:31 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/07/26 14:10:34 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	w_e_m(char *message, char *add)
{
	if (add)
		write(2, add, ft_strlen(add));
	if (message)
		write(2, message, ft_strlen(message));
	return (127);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	if (!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while ((*s != c) && (*s != '\0'))
	{
		s++;
	}
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

char	***split_on_pipes(char **args)
{
	int		i;
	int		j;
	int		seg_i;
	int		seg_count;
	char	***segs;

	seg_count = count_pipe_lines(args);
	seg_i = 0;
	j = 0;
	i = 0;
	segs = ft_calloc(seg_count + 1, sizeof(char **));
	if (!segs)
		return (NULL);
	while (args[i])
	{
		if (!ft_strncmp(args[i], "|", 2))
		{
			segs[seg_i++] = dup_pipe_lines(args, j, i);
			j = i + 1;
		}
		i++;
	}
	segs[seg_i++] = dup_pipe_lines(args, j, i);
	segs[seg_i] = NULL;
	return (segs);
}
