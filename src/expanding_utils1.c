/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:51:02 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/13 01:57:30 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

static char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!key)
		return (NULL);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		key[i] = str[i];
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '+')
		return (free(key), NULL);
	key[i] = '\0';
	return (key);
}

static char	*get_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!value)
		return (NULL);
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] != '=')
		return (free(value), NULL);
	j++;
	while (str[j])
	{
		value[i] = str[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

static char	*get_sep(char *str)
{
	char	*sep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sep = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!sep)
		return (NULL);
	while (str[j] && str[j] != '=' && str[j] != '+')
		j++;
	if (str[j] == '=')
	{
		sep[i++] = '=';
		sep[i++] = '\0';
	}
	else if (str[j] == '+' && str[j + 1] == '=')
	{
		sep[i++] = '+';
		sep[i++] = '=';
		sep[i] = '\0';
	}
	else
		return (NULL);
	return (sep);
}

char	*get_str(char *var, char *type)
{
	if (!var || !type)
		return (NULL);
	if (ex_strcmp(type, "key") == 0)
		return (get_key(var));
	else if (ex_strcmp(type, "value") == 0)
		return (get_value(var));
	else if (ex_strcmp(type, "sep") == 0)
		return (get_sep(var));
	return (NULL);
}

t_env	*new_variable(char *env_key, char *env_value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = env_key;
	node->value = env_value;
	node->next = NULL;
	return (node);
}
