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

void	free_segments(char ***segs)
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
