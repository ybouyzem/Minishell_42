/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:34:54 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 11:11:01 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

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

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)my_malloc(size + 1, 1);
	if (str == NULL)
		return (my_malloc(0, 0), exit(10), NULL);
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
