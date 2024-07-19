/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merging.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:28:33 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/31 11:07:44 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	to_merge(t_token *current)
{
	return (
		(current->type == WORD
			|| current->type == ENV_VAR
			|| current->type == WILDCARD)
		&& current->next
		&& (current->next->type == WORD
			|| current->next->type == ENV_VAR
			|| current->next->type == WILDCARD));
}

void	merge_near_word(t_token **token)
{
	t_token	*current;
	t_token	*to_free;

	current = *token;
	while (current != NULL)
	{
		if (to_merge(current))
		{
			current->extract = ft_freejoin(current->extract,
					current->next->extract);
			to_free = current->next;
			current->next = current->next->next;
			free(to_free->extract);
			free(to_free);
		}
		else
		{
			current = current->next;
		}
	}
}
