/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:34:16 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:34:28 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("%s=%s\n", tmp->name, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
