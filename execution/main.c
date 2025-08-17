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

int	g_signal_status = 0;

void	sigint_handler(int signo)
{
	(void)signo;
	g_signal_status = 130;
	if (*running_instance())
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	if (*input == '\0')
	{
		free(input);
		return (1);
	}
	return (2);
}

void	main_loop(t_env **env_list, int *exit_status)
{
	char	*input;
	int		status;

	while (1)
	{
		*running_instance() = true;
		input = readline("minishell> ");
		*running_instance() = false;
		if (g_signal_status != 0)
		{
			*exit_status = g_signal_status;
			g_signal_status = 0;
		}
		status = check_readline(input);
		if (status == 0)
			break ;
		else if (status == 1)
			continue ;
		handle_input(input, env_list, exit_status);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env_list;
	int		exit_status;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env_list = set_env(envp);
	exit_status = 0;
	main_loop(&env_list, &exit_status);
	free_list(env_list);
	return (exit_status);
}
