/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balanced_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:53:18 by smontuor42        #+#    #+#             */
/*   Updated: 2024/06/01 12:13:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	are_double_quotes_balanced(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			count++;
		}
		i++;
	}
	return (count % 2 == 0);
}

static int	are_single_quotes_balanced(const char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			count++;
		}
		i++;
	}
	return (count % 2 == 0);
}

static int	are_parentheses_balanced(const char *str)
{
	int	balance;
	int	i;

	balance = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			balance++;
		}
		else if (str[i] == ')')
		{
			balance--;
		}
		if (balance < 0)
		{
			return (0);
		}
		i++;
	}
	return (balance == 0);
}

int	check_balance(const char *str)
{
	char	c;

	c = 0;
	if (are_single_quotes_balanced(str) == 0)
		c = '\'';
	if (are_double_quotes_balanced(str) == 0)
		c = '"';
	if (are_parentheses_balanced(str) == 0)
		c = '(';
	if (c)
	{
		ft_printf_fd(2,
			"minishell: parse error, token `%c' not balanced\n", c);
		return (0);
	}
	return (1);
}
