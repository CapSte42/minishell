/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:28:28 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/18 16:49:15 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_processing(t_token **token_list, t_token **head,
		t_state *state)
{
	*head = *token_list;
	*state = INIT;
}

void	handle_single_quote_state(t_token *head, t_state *state)
{
	if (head->type == S_QUOTE)
	{
		*state = INIT;
		head->type = WORD;
	}
	else
	{
		head->type = WORD;
		head->exception = 0;
	}
}

void	handle_init_state(t_token *head, t_state *state)
{
	if (head->type == S_QUOTE || head->type == D_QUOTE)
	{
		if (head->type == S_QUOTE)
			*state = IN_SINGLE_QUOTE;
		else
			*state = IN_DOUBLE_QUOTE;
		head->type = WORD;
		head->exception = 0;
	}
}

void	handle_double_quote_state(t_token *head, t_state *state)
{
	if (head->type == D_QUOTE)
	{
		*state = INIT;
		head->type = WORD;
		head->exception = 0;
	}
	else
	{
		head->type = WORD;
		head->exception = 0;
	}
}

void	quote_handling(t_token **token_list)
{
	t_state	state;
	t_token	*head;

	initialize_processing(token_list, &head, &state);
	while (head)
	{
		if (state == INIT)
		{
			handle_init_state(head, &state);
		}
		else if (state == IN_SINGLE_QUOTE)
		{
			handle_single_quote_state(head, &state);
		}
		else if (state == IN_DOUBLE_QUOTE)
		{
			handle_double_quote_state(head, &state);
		}
		head = head->next;
	}
}
