/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:07:24 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 11:45:40 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_quotes(int *single_quote, int *double_quote, char c)
{
	if (c == '\'' && !*single_quote)
		*double_quote = !*double_quote;
	else if (c == '"' && !*double_quote)
		*single_quote = !*single_quote;
}

void	add_spaces_helper1(char **new, char *input, int *i, int *j)
{
	(*new)[*j] = input[*i];
	(*i)++;
	(*j)++;
}

void	add_spaces_helper2(char **new, char *input, int *i, int *j)
{
	(*new)[*j] = ' ';
	(*j) += 1;
	(*new)[*j] = input[*i];
	(*j) += 1;
	(*new)[*j] = ' ';
	(*j)++;
	(*i)++;
}

void	add_spaces_helper3(char **new, char *input, int *i, int *j)
{
	(*new)[*j] = ' ';
	(*j) += 1;
	(*new)[*j] = input[*i];
	(*j) += 1;
	(*new)[*j] = input[*i + 1];
	(*j) += 1;
	(*new)[*j] = ' ';
	(*i)++;
	(*j)++;
	(*i)++;
}

char	*add_spaces(char *input, int single_quote, int double_quote)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	vars.new
		= (char *)my_malloc(((ft_strlen(input) * 2) + 1) * sizeof(char), 1);
	if (!vars.new)
		(my_malloc(0, 0), exit(10));
	while (input[vars.i])
	{
		ft_check_quotes(&single_quote, &double_quote, input[vars.i]);
		if (!single_quote && !double_quote)
		{
			if (input[vars.i + 1] && is_redirection(input, vars.i) == 2)
				add_spaces_helper3(&vars.new, input, &vars.i, &vars.j);
			else if (input[vars.i] == '|' || input[vars.i]
				== '<' || input[vars.i] == '>')
				add_spaces_helper2(&vars.new, input, &vars.i, &vars.j);
			else
				add_spaces_helper1(&vars.new, input, &vars.i, &vars.j);
		}
		else
			add_spaces_helper1(&vars.new, input, &vars.i, &vars.j);
	}
	vars.new[vars.j] = '\0';
	return (vars.new);
}
