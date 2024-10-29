/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:32:24 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 11:50:16 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

t_heredoc	*lst_heredoc_new(char *delimiter, char *file)
{
	t_heredoc	*new;

	new = (t_heredoc *)my_malloc(sizeof(t_heredoc), 1);
	if (!new)
		return (NULL);
	new->delimiter = delimiter;
	new->file = file;
	new->buffer = NULL;
	new->will_expand = 0;
	new->next = NULL;
	return (new);
}

void	lst_heredoc_add_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*p;

	p = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

int	is_any_heredoc(char **red)
{
	int	i;

	i = 0;
	if (!red || !red[0])
		return (0);
	while (red[i])
	{
		if (ex_strcmp(red[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	clear_herdocs(t_path *path)
{
	t_heredoc	*current;

	current = path->heredoc;
	while (current)
	{
		unlink(current->file);
		current = current->next;
	}
	path->heredoc = NULL;
}
