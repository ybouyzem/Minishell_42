/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:43:21 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/14 13:45:13 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

void	count_dollars(t_vars *vars, char *str)
{
	vars->i += 1;
	vars->start = 1;
	while (str[vars->i] == '$' && str[vars->i])
	{
		vars->start++;
		vars->i++;
	}
}

void	add_dollars(t_vars *vars, int c)
{
	vars->start = vars->start / 2;
	if (c == 1)
	{
		while (vars->start)
		{
			vars->new = ft_strjoin(vars->new, "$");
			vars->start--;
		}
	}
	else if (c == 2)
	{
		while (vars->start >= 1)
		{
			vars->new = ft_strjoin(vars->new, "$");
			vars->start--;
		}
	}
}
