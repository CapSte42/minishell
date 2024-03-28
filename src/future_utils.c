/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:53:18 by smontuor42        #+#    #+#             */
/*   Updated: 2024/03/28 04:16:00 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	are_quotes_balanced(const char* str)
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

int	are_single_quotes_balanced(const char* str)
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

int are_parentheses_balanced(const char* str)
{
	int balance;
	int i;

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

