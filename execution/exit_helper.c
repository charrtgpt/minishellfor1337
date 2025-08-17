/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-ijj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:39:15 by mait-ijj          #+#    #+#             */
/*   Updated: 2025/08/17 21:39:17 by mait-ijj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_if_interactive(void)
{
	if (isatty(0) && isatty(1))
		write(2, "exit\n", 5);
}

int	norm_status(long long v)
{
	int	s;

	s = (int)(v % 256);
	if (s < 0)
		s += 256;
	return (s);
}

size_t	skip_spaces(const char *s, size_t i)
{
	while (s[i] && isspace((unsigned char)s[i]))
		i++;
	return (i);
}

int	get_sign(const char *s, size_t *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	convert_digits(const char *s, size_t *i,
		unsigned long long *acc, int sign)
{
	unsigned long long	lim_pos;
	unsigned long long	lim_neg;
	int					has_digit;

	lim_pos = (unsigned long long)LLONG_MAX;
	lim_neg = (unsigned long long)LLONG_MAX + 1ULL;
	has_digit = 0;
	while (ft_isdigit((unsigned char)s[*i]))
	{
		has_digit = 1;
		*acc = *acc * 10ULL + (unsigned long long)(s[*i] - '0');
		if ((sign == 1 && *acc > lim_pos)
			|| (sign == -1 && *acc > lim_neg))
			return (0);
		(*i)++;
	}
	return (has_digit);
}
