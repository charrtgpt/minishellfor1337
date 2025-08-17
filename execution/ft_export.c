/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:23:34 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:23:37 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	sort_env(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_env *env)
{
	char	**arr;
	int		i;
	char	*eq;

	arr = list_to_array(env);
	if (!arr)
		return ;
	sort_env(arr);
	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		eq = ft_strchr(arr[i], '=');
		if (eq)
		{
			printf("%.*s", (int)(eq - arr[i] + 1), arr[i]);
			printf("\"%s\"", eq + 1);
		}
		else
			printf("%s", arr[i]);
		printf("\n");
		i++;
	}
	free_str(arr);
}

int	ft_export(char **args, t_env **env)
{
	int	i;

	if (!args[1])
		return (print_export(*env), 0);
	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			w_e_m(args[i], "minishell: export: `");
			write(2, "`: not a valid identifier\n", 26);
			return (1);
		}
		else
			env_add_or_update(env, args[i]);
		i++;
	}
	return (0);
}
