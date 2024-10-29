/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:30:36 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 17:22:27 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

char	*my_get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = (char *)my_malloc(sizeof(char) * ft_strlen(str) + 1, 1);
	if (!key)
		return (NULL);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		key[i] = str[i];
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '+')
		return (NULL);
	key[i] = '\0';
	return (key);
}

char	*my_get_value(char *str)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = (char *)my_malloc(sizeof(char) * ft_strlen(str) + 1, 1);
	if (!value)
		return (NULL);
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] != '=')
		return (NULL);
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

char	*my_get_sep(char *str)
{
	char	*sep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sep = (char *)my_malloc(sizeof(char) * ft_strlen(str) + 1, 1);
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

static int	ft_size(long n)
{
	int	size;

	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		size = 1;
	}
	else
		size = 0;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*my_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)my_malloc(size + 1, 1);
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	size -= 1;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n == 0)
		str[size] = 48;
	while (n > 0)
	{
		str[size] = n % 10 + '0';
		n /= 10;
		size--;
	}
	return (str);
}
