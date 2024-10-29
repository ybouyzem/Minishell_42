/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 08:33:12 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/13 01:37:22 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redirections_helper(char *input, int *i, int *j, char c)
{
	if (c == '>')
	{
		while (input[*i] == '>' && input[*i])
		{
			*j = *j + 1;
			*i = *i + 1;
		}
		if (*j > 2)
			return (-2);
	}
	else if (c == '<')
	{
		while (input[*i] == '<' && input[*i])
		{
			*j = *j + 1;
			*i = *i + 1;
		}
		if (*j > 2)
			return (-1);
	}
	return (0);
}

int	check_redirections(char *input)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (input[vars.i] == '|')
		return (-1);
	while (input[vars.i])
	{
		vars.j = 0;
		ft_check_quotes(&vars.single_quote, &vars.double_quote, input[vars.i]);
		if (!vars.single_quote && !vars.double_quote)
		{
			if (check_redirections_helper(input, &vars.i, &vars.j, '<') == -1)
				return (-1);
			vars.j = 0;
			if (check_redirections_helper(input, &vars.i, &vars.j, '>') == -2)
				return (-2);
			if (input[vars.i] != '\0' && input[vars.i] != '<'
				&& input[vars.i] != '>')
				vars.i++;
		}
		else
			vars.i++;
	}
	return (1);
}

int	check_syntax_helper(char *input, int i, int j, char c)
{
	if (c == '>')
	{
		if (input[i] == '\0')
			return (-1);
		if (j + 1 != i && input[i] == '>')
			return (-2);
		else if (input[i] == '<')
			return (-3);
		else if (input[i] == '|')
			return (-4);
	}
	else if (c == '<')
	{
		if (input[i] == '|')
			return (-4);
		else if (i != j && input[i] == '<')
			return (-3);
		else if (input[i] == '>')
			return (-2);
		else if (input[i] == '\0')
			return (-1);
	}
	return (1);
}

int	check_syntax_helper1(char *input, int *i, int j)
{
	if (is_redirection(input, *i) == 2)
	{
		*i = skip_spaces(input, *i + 1, &j);
		if (input[*i] == '|')
			return (-1);
	}
	if (input[*i] == '>')
	{
		*i = skip_spaces(input, *i + 1, &j);
		if (check_syntax_helper(input, *i, j, '>') < 0)
			return (check_syntax_helper(input, *i, j, '>'));
	}
	if (input[*i] == '<')
	{
		*i = skip_spaces(input, *i + 1, &j);
		if (check_syntax_helper(input, *i, j, '<') < 0)
			return (check_syntax_helper(input, *i, j, '<'));
	}
	if (input[*i] == '|')
	{
		*i = skip_spaces(input, *i + 1, &j);
		if (input[*i] == '|' || input[*i] == '\0')
			return (-4);
	}
	return (1);
}

int	check_syntax(char *input)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (check_redirections(input) == -1 || check_quotes(input) == -1)
		return (-1);
	if (check_redirections(input) == -2)
		return (-2);
	if ((is_redirection(input, 0) == 2 && input[vars.i + 2] == '\0')
		|| (is_redirection(input, 0) && input[vars.i + 1] == '\0'))
		return (-2);
	while (input[vars.i])
	{
		vars.j = vars.i;
		ft_check_quotes(&vars.single_quote, &vars.double_quote, input[vars.i]);
		if (!vars.single_quote && !vars.double_quote)
		{
			vars.start = check_syntax_helper1(input, &vars.i, vars.j);
			if (vars.start < 0)
				return (vars.start);
		}
		vars.i = vars.j;
		vars.i++;
	}
	return (1);
}
