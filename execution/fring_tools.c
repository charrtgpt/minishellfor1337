/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fring_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 19:28:54 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/13 19:28:57 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_pipelines(char ***segs)
{
	int	i;

	i = 0;
	if (!segs)
		return ;
	while (segs[i])
	{
		free_str(segs[i]);
		i++;
	}
	free(segs);
}

void	free_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	cleanup(t_tofree *tofree, int i)
{
	if (!tofree)
		return ;
	if (tofree->pipelines)
		free_pipelines(tofree->pipelines);
	if (tofree->env)
		free_list(*tofree->env);
	if (tofree->pids)
		free(tofree->pids);
	if (tofree->pars && i == 1)
		free_str(tofree->pars);
	if (tofree->envp)
		free_str(tofree->envp);
}
