/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporthelper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:19:11 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:19:19 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static t_env	*env_new_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

static int	env_update(t_env *env, char *name, char *value)
{
	int	len;

	while (env)
	{
		len = (int)ft_strlen(env->name);
		if (ft_strncmp(env->name, name, len) == 0 && name[len] == '\0')
		{
			if (value)
			{
				free(env->value);
				env->value = value;
			}
			free(name);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	env_add(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = env_new_node(name, value);
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = env_new_node(name, value);
}

void	env_add_or_update(t_env **env, char *arg)
{
	char	*name;
	char	*value;
	char	*eq;
	int		updated;

	if (!arg || !env)
		return ;
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		name = ft_substr(arg, 0, eq - arg);
		value = ft_strdup(eq + 1);
	}
	else
	{
		name = ft_strdup(arg);
		value = NULL;
	}
	updated = env_update(*env, name, value);
	if (!updated)
		env_add(env, name, value);
}
