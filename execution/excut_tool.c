/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:12:07 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:12:10 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closee_and_exit(int *sv, char **clean, int *status, int value)
{
	dup2(sv[0], STDIN_FILENO);
	dup2(sv[1], STDOUT_FILENO);
	close(sv[0]);
	close(sv[1]);
	if (clean)
		free_str(clean);
	*status = value;
}

void	create_file_only(char **args, char **clean, int *status)
{
	int	i;
	int	type;
	int	sv[2];

	i = 0;
	sv[0] = dup(STDIN_FILENO);
	sv[1] = dup(STDOUT_FILENO);
	while (args[i])
	{
		type = find_r_type(args[i]);
		if (type && args[i + 1])
		{
			if (re_direction(args[i + 1], type) == -1)
			{
				closee_and_exit(sv, clean, status, 1);
				return ;
			}
			i += 2;
		}
		else
			i++;
	}
	closee_and_exit(sv, clean, status, 0);
}

void	handle_env_error(char *cmd, char **clean, t_tofree *fr)
{
	write(2, "minishell: ", 11);
	w_e_m(": No such file or directory\n", cmd);
	free_str(clean);
	child_exit(fr, 127, 1);
}
