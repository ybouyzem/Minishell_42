/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:42:53 by alamini           #+#    #+#             */
/*   Updated: 2024/10/17 11:45:10 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (waitpid(-1, &sig, WNOHANG) == 0)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_signal = SIGINT;
}

void	herdoc_sig_handler(int sig)
{
	(void)sig;
	close(0);
	g_last_signal = SIGINT;
}

void	setup_signals(int action)
{
	if (action == SET_SIG)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (action == UNSET_SIG)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (action == HERDOC_SIG)
	{
		signal(SIGINT, herdoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}
