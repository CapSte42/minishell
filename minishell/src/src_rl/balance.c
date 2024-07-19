/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:35:59 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/16 20:59:48 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	check_quote_balance(char *rl)
{
	t_state	quote_state;

	quote_state = INIT;
	while (*rl)
	{
		if (quote_state == INIT)
		{
			if (*rl == '\'')
				quote_state = IN_SINGLE_QUOTE;
			else if (*rl == '\"')
				quote_state = IN_DOUBLE_QUOTE;
		}
		else if (quote_state == IN_SINGLE_QUOTE)
		{
			if (*rl == '\'')
				quote_state = INIT;
		}
		else if (quote_state == IN_DOUBLE_QUOTE)
		{
			if (*rl == '\"')
				quote_state = INIT;
		}
		rl++;
	}
	return (quote_state);
}

static t_state	handle_init_state(char *rl, int *paren_count)
{
	t_state	quote_state;

	quote_state = INIT;
	if (*rl == '\'')
		quote_state = IN_SINGLE_QUOTE;
	else if (*rl == '\"')
		quote_state = IN_DOUBLE_QUOTE;
	else if (*rl == '(')
	{
		(*paren_count)++;
		quote_state = IN_PARENTHESES;
	}
	else if (*rl == ')')
	{
		(*paren_count)--;
		if (*paren_count == 0)
			quote_state = INIT;
	}
	return (quote_state);
}

static t_state	handle_quote_states(char *rl, t_state quote_state)
{
	if (quote_state == IN_SINGLE_QUOTE)
	{
		if (*rl == '\'')
			quote_state = INIT;
	}
	else if (quote_state == IN_DOUBLE_QUOTE)
	{
		if (*rl == '\"')
			quote_state = INIT;
	}
	return (quote_state);
}

static t_state	handle_parentheses_state(char *rl, int *paren_count)
{
	t_state	quote_state;

	quote_state = IN_PARENTHESES;
	if (*rl == '(')
		(*paren_count)++;
	else if (*rl == ')')
	{
		(*paren_count)--;
		if (*paren_count == 0)
			quote_state = INIT;
	}
	return (quote_state);
}

t_state	check_paren_balance(char *rl)
{
	int		paren_count;
	t_state	quote_state;

	paren_count = 0;
	quote_state = INIT;
	while (*rl)
	{
		if (quote_state == INIT)
			quote_state = handle_init_state(rl, &paren_count);
		else if (quote_state == IN_SINGLE_QUOTE
			|| quote_state == IN_DOUBLE_QUOTE)
			quote_state = handle_quote_states(rl, quote_state);
		else if (quote_state == IN_PARENTHESES)
			quote_state = handle_parentheses_state(rl, &paren_count);
		rl++;
	}
	if (paren_count > 0)
		return (IN_PARENTHESES);
	if (paren_count < 0)
		return (ERROR);
	return (quote_state);
}
