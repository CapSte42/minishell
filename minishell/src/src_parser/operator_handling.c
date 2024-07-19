/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:28:56 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/31 11:06:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_logic_operator(t_token *prev, t_token *current,
		t_token *next, int *flag)
{
	if (prev == NULL || next == NULL)
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (prev->exception == 1 || next->exception == 1)
	{
		*flag = print_syntax_error(next->extract);
	}
	else if (current->type == PIPE)
	{
		if (prev != NULL && prev->extract[0] == ')')
		{
			*flag = print_syntax_error(current->extract);
		}
		else if (next != NULL && next->extract[0] == '(')
		{
			*flag = print_syntax_error(current->extract);
		}
	}
}

void	handle_redirect_operator(t_token *prev, t_token *current,
		t_token *next, int *flag)
{
	if (next == NULL)
	{
		*flag = print_syntax_error("newline");
	}
	else if (next->exception != 0)
	{
		*flag = print_syntax_error(next->extract);
	}
	else if (next->exception == 0)
	{
		if (ft_strchr(next->extract, '\n') != NULL)
			*flag = print_syntax_error("newline");
		else if (ft_strncmp(next->extract, "*\0", 2) == 0)
			*flag = print_syntax_error("ambiguous redirect");
	}
	else if (prev != NULL && prev->exception == 4)
	{
		*flag = print_syntax_error(current->extract);
	}
}

void	handle_parenthesis_open_operator(t_token *prev, t_token *current,
		t_token *next, int *flag)
{
	if (next == NULL)
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (prev != NULL && (prev->exception != 1 && prev->exception != 3))
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (next != NULL && next->exception == 1)
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (next != NULL && next->exception == 4)
	{
		*flag = print_syntax_error(next->extract);
	}
}

void	handle_parenthesis_close_operator(t_token *prev, t_token *current,
		t_token *next, int *flag)
{
	if (prev == NULL)
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (prev->exception == 1)
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (next != NULL && (next->exception != 1 && next->exception != 4))
	{
		*flag = print_syntax_error(current->extract);
	}
	else if (next != NULL && next->type == PIPE)
	{
		*flag = print_syntax_error(next->extract);
	}
}

void	handle_word_operator(t_token *prev, t_token *current, t_token *next,
		int *flag)
{
	if (prev == NULL)
	{
		current->type = CMD;
	}
	else if (prev != NULL && prev->exception == 1)
	{
		current->type = CMD;
	}
	else if (prev != NULL && prev->exception == 3)
	{
		current->type = CMD;
	}
	else if (prev != NULL && prev->exception == 2)
	{
		if (next != NULL && next->exception == 3)
			*flag = print_syntax_error(next->extract);
	}
}
