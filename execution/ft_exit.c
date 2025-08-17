/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:37:44 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:37:46 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_numeric(const char *s, long long *out)
{
	unsigned long long	acc;
	size_t				i;
	int					sign;
	int					has_digit;

	acc = 0;
	i = 0;
	i = skip_spaces(s, i);
	sign = get_sign(s, &i);
	has_digit = convert_digits(s, &i, &acc, sign);
	if (!has_digit)
		return (0);
	i = skip_spaces(s, i);
	if (s[i] != '\0')
		return (0);
	if (sign == 1)
		*out = (long long)acc;
	else
		*out = -(long long)acc;
	return (1);
}

static int	print_numeric_error(const char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, (int)ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	return (2);
}

static int	print_too_many_args(void)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}

static int	handle_exit_args(char **args, int ac, t_tofree *fr, int last_status)
{
	long long	val;
	int			ok;

	if (ac == 1)
	{
		print_exit_if_interactive();
		free_str(args);
		child_exit(fr, last_status, 1);
	}
	ok = parse_numeric(args[1], &val);
	if (!ok)
	{
		print_exit_if_interactive();
		print_numeric_error(args[1]);
		free_str(args);
		child_exit(fr, 2, 1);
	}
	if (ac > 2)
		return (print_too_many_args());
	print_exit_if_interactive();
	free_str(args);
	child_exit(fr, norm_status(val), 1);
	return (0);
}

int	ft_exit(char **args, int last_status, t_tofree *fr)
{
	int	ac;

	ac = 0;
	while (args && args[ac])
		ac++;
	return (handle_exit_args(args, ac, fr, last_status));
}
