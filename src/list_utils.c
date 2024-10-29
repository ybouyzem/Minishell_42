/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:23:57 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 08:54:25 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lstsize(t_command *lst)
{
	int			i;
	t_command	*p;

	p = lst;
	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}

t_command	*lstlast(t_command *lst)
{
	t_command	*p;
	int			size;
	int			i;

	i = 0;
	p = lst;
	size = lstsize(lst);
	while (i < size - 1)
	{
		p = p->next;
		i++;
	}
	return (p);
}

void	lstadd_back(t_command **lst, t_command *new)
{
	t_command	*p;

	p = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		p = lstlast(*lst);
		p->next = new;
	}
}

// t_command	*lstnew(char **cmd, char **red)
// {
// 	t_command	*new;

// 	new = (t_command *)my_malloc(sizeof(t_command), 1);
// 	if (!new)
// 		return (my_malloc(0, 0), exit(10), NULL);
// 	new->cmd = cmd;
// 	new->redirection = red;
// 	new->next = NULL;
// 	return (new);
// }

void	print_list(t_command *lst)
{
	t_command	*p;

	p = lst;
	while (p != NULL)
	{
		puts("node :\n");
		printf("cmd: ");
		printstrs(p->cmd);
		printf("redirection: ");
		printstrs(p->redirection);
		puts("******************\n\n");
		p = p->next;
	}
}
