/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:31:50 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:31:52 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_arg(char *arg, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	node = *env;
	if (ft_strcmp(node->name, arg) == 0)
	{
		*env = node->next;
		free_env_node(node);
		return ;
	}
	while (node && node->next)
	{
		if (ft_strcmp(node->next->name, arg) == 0)
		{
			tmp = node->next;
			node->next = tmp->next;
			free_env_node(tmp);
			return ;
		}
		node = node->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int		i;

	if (!args || !env)
		return (0);
	i = 1;
	while (args[i])
	{
		remove_arg(args[i], env);
		i++;
	}
	return (0);
}
