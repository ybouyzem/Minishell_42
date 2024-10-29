/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:51:25 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/20 15:38:18 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

int	g_last_signal = 0;

static t_path	*init_data(t_path *path, t_env *env)
{
	path = (t_path *)malloc(sizeof(t_path));
	if (!path)
		malloc_error(path, env);
	path->main_path = NULL;
	path->pwd = NULL;
	path->exit_status = 0;
	path->is_forked = 0;
	path->fd_in = 0;
	path->fd_out = 1;
	path->heredoc = NULL;
	path->main_path = malloc(sizeof(char) * PATH_MAX);
	if (!path->main_path)
		malloc_error(path, env);
	if (!getcwd(path->main_path, PATH_MAX))
	{
		free(path->main_path);
		path->main_path = ft_strdup("/");
	}
	path->pwd = ft_strdup(path->main_path);
	if (!path->pwd)
		malloc_error(path, env);
	return (path);
}

void	get_cmds_execute_clear(t_vars vars, t_command *cmds,
	t_env **env_vars, t_path *path)
{
	vars.tmp = add_spaces(vars.tmp, 0, 0);
	vars.tmp = ft_strtrim(vars.tmp, " ");
	vars.args = split_args(vars.tmp);
	cmds = split_cmds(vars.args, *env_vars, path);
	path->is_forked = 0;
	execute(cmds, env_vars, path);
	clear_herdocs(path);
	my_malloc(0, 0);
}

void	while_loop(t_command *cmds, t_path *path,
	t_env **env_vars, struct termios *attrs)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	while (1)
	{
		vars.input = readline("minishell $> ");
		if (!vars.input)
			break ;
		path->is_forked = 0;
		add_history(vars.input);
		if (is_only_spaces(vars.input))
		{
			free(vars.input);
			continue ;
		}
		vars.tmp = ft_strtrim(vars.input, " ");
		free(vars.input);
		if (check_syntax(vars.tmp) < 0)
		{
			(syn_err_messages(check_syntax(vars.tmp)), exit_status(258, path));
			continue ;
		}
		get_cmds_execute_clear(vars, cmds, env_vars, path);
		tty_attributes(attrs, ATTR_SET);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	attrs[3];
	t_command		*cmds;
	t_env			*env_vars;
	t_path			*path;

	if (argc != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	((void)argc, (void)argv);
	env_vars = NULL;
	cmds = NULL;
	path = NULL;
	set_up(attrs);
	env_vars = full_envs(envp);
	path = init_data(path, env_vars);
	while_loop(cmds, path, &env_vars, attrs);
	free_and_exit(path, env_vars);
}
