/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:46:59 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 12:26:06 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit(t_path *path, t_env *env_vars)
{
	int	exit_state;

	exit_state = path->exit_status;
	free_envs(env_vars);
	free(path->pwd);
	free(path->main_path);
	free(path);
	exit(exit_state);
}

void	free_envs(t_env *envs)
{
	t_env	*current;
	t_env	*tmp;

	current = envs;
	while (current)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
}
