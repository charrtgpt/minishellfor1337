/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:07:05 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/15 16:07:08 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_node(const char *name, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	if (!node->name)
		return (free(node), NULL);
	if (value != NULL)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->name), free(node), NULL);
	}
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	set_next(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	increment_shlvl(t_env *env_list)
{
	t_env	*tmp;
	int		level;
	char	*new_value;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "SHLVL", 6) == 0)
		{
			if (tmp->value != NULL)
				level = ft_atoi(tmp->value);
			else
				level = 0;
			level++;
			free(tmp->value);
			new_value = ft_itoa(level);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	set_next(&env_list, init_node("SHLVL", "1"));
}

t_env	*set_env(char **envp)
{
	t_env	*env_list;
	char	*separ;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		separ = ft_strchr(envp[i], '=');
		if (separ)
		{
			*separ = '\0';
			set_next(&env_list, init_node(envp[i], separ + 1));
			*separ = '=';
		}
		i++;
	}
	increment_shlvl(env_list);
	return (env_list);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_env	*list;

// 	list = set_env(env);
// 	while (list->next)
// 	{
// 		printf("%s=", list->name);
// 		printf("%s\n", list->value);
// 		list = list->next;
// 	}
// 	printf("%s=", list->name);
// 	printf("%s\n", list->value);
// }
