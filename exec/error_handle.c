/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:04 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 17:27:52 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

void	envp_error(t_env *env)
{
	write(2, "Allocation Error\n", 17);
	free_envs(env);
	exit(1);
}

void	fd_error(t_path *path, t_env *env)
{
	write(2, "File descriptor Error\n", 22);
	if (path->fd_in >= 0)
		close(path->fd_in);
	if (path->fd_out >= 0)
		close(path->fd_out);
	my_malloc(0, 0);
	free_envs(env);
	free(path->main_path);
	free(path->pwd);
	free(path);
	exit(1);
}

void	malloc_error(t_path *path, t_env *env)
{
	write(2, "Allocation Error\n", 17);
	if (path->fd_in >= 0)
		close(path->fd_in);
	if (path->fd_out >= 0)
		close(path->fd_out);
	my_malloc(0, 0);
	free_envs(env);
	if (path->main_path)
		free(path->main_path);
	if (path->pwd)
		free(path->pwd);
	if (path)
		free(path);
	exit(1);
}

void	print_error(char *cmd, char *path, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error)
		ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
