/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <mait-ijj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:57:42 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/05/16 22:16:40 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\nminishell> ", 12);
}

void	sigquit_handler(int signo)
{
	(void)signo;
}

int	check_readline(char *input)
{
	if (!input)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strncmp(input, "exit", 5) == 0)
	{
		free(input);
		write(1, "exit\n", 5);
		return (0);
	}
	if (*input == '\0')
	{
		free(input);
		return (1);
	}
	return (2);
}

int	main(int ac, char **av, char **envp)
{
	char	**pars;
	char	*input;
	char	***pipelines;
	char	**my_env;
	t_env	*env_list;
	int		n_pipelines;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		input = readline("minishell> ");
		if (check_readline(input) == 0)
			return (0);
		else if (check_readline(input) == 1)
			continue ;
		add_history(input);
		pars = call_f(input);
		free(input);
		env_list = set_env(envp);
		my_env = list_to_array(env_list);
		if (if_pipe(pars))
		{
			pipelines = split_on_pipes(pars);
			n_pipelines = count_pipe_lines(pars);
			execute_pipeline(pipelines, my_env, n_pipelines);
			free_pipelines(pipelines);
		}
		else
		{
			execute_command_with_redirection(pars, my_env);
		}
		free_list(env_list);
		free_str(my_env);
		free_str(pars);
	}
}
