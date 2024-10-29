/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:47:13 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 21:40:50 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static int	is_valid_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n' && str[i])
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

static void	echo_it(t_command *command, int i, int new_line)
{
	while (command->cmd[i])
	{
		ft_putstr_fd(command->cmd[i], 1);
		if (command->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
}

int	echo(t_command *command)
{
	int	is_valid;
	int	new_line;
	int	i;

	i = 1;
	new_line = 1;
	is_valid = 0;
	while (command->cmd[i] && is_valid == 0)
	{
		is_valid = is_valid_option(command->cmd[i]);
		if (is_valid == 0)
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	echo_it(command, i, new_line);
	return (0);
}
