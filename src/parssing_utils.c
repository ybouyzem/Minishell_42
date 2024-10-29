/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 06:36:26 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 12:51:50 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

void	syn_err_messages(int code)
{
	if (code == -1)
		write(2, "Minishell: syntax error \n", 26);
	else if (code == -2)
		write(2, "Minishell: syntax error near unexpected token `>'\n", 51);
	else if (code == -3)
		write(2, "Minishell: syntax error near unexpected token `<'\n", 51);
	else if (code == -4)
		write(2, "bash: syntax error near unexpected token `|'\n", 46);
}

int	is_redirection(char *str, int index)
{
	if (str[index] == '>' && str[index + 1] == '>')
		return (2);
	if (str[index] == '<' && str[index + 1] == '<')
		return (2);
	if (str[index] == '<' || str[index] == '>')
		return (1);
	return (0);
}

int	skip_spaces(char *str, int index, int *j)
{
	*j = index;
	while (ft_isspace(str[index]) && str[index])
		index++;
	return (index);
}

void	remove_spaces(char **input)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	res = *input;
	start = 0;
	i = 0;
	if (!res)
		return ;
	while (ft_isspace(*res))
		res++;
	end = ft_strlen(res) - 1;
	while (end >= start && ft_isspace(res[end]))
		end--;
	res[end + 1] = '\0';
	*input = res;
}

int	check_quotes(char	*input)
{
	int		i;
	int		single_quote;
	int		double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !single_quote)
			double_quote = !double_quote;
		else if (input[i] == '"' && !double_quote)
			single_quote = !single_quote;
		i++;
	}
	if (single_quote || double_quote)
		return (-1);
	return (1);
}
