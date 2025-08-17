/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlerss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 02:38:42 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/16 02:38:44 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input(char *input, t_env **env_list, int *exit_status)
{
	char		**pars;
	t_tofree	fr;
	char		**my_env;

	add_history(input);
	pars = call_f(input);
	free(input);
	my_env = list_to_array(*env_list);
	fr.env = env_list;
	fr.pipelines = NULL;
	fr.pids = NULL;
	fr.pars = pars;
	fr.envp = my_env;
	if (if_pipe(pars))
	{
		fr.pipelines = split_on_pipes(pars);
		execute_pipeline(fr.pipelines, my_env, &fr, exit_status);
		free_pipelines(fr.pipelines);
	}
	else
		execute_command_with_redirection(pars, my_env, exit_status, &fr);
	free_str(my_env);
	free_str(pars);
	return (1);
}

bool	*running_instance(void)
{
	static bool	running = false;

	return (&running);
}
