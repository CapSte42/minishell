/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:51:39 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/05 10:06:34 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exception_token(t_type type)
{
	int	flag;

	flag = 0;
	flag += ((type == PARENTHESIS_C) * 4);
	flag += ((type == PARENTHESIS_O) * 3);
	flag += (isredirection_operator(type) * 2);
	flag += islogical_operator(type);
	return (flag);
}

void	set_token(t_token **token, t_type type, int start, char *extract)
{
	(*token)->type = type;
	(*token)->exception = is_exception_token(type);
	(*token)->start = start;
	(*token)->end = start + ft_strlen(extract);
	(*token)->extract = extract;
	(*token)->next = NULL;
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		if (tmp->extract)
			free(tmp->extract);
		free(tmp);
	}
	*token = NULL;
}

void	add_token(t_token **token, t_type type, int start, char *extract)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		exit(1);
	set_token(&new_token, type, start, extract);
	if (*token == NULL)
		*token = new_token;
	else
	{
		last = *token;
		while (last->next != NULL)
			last = last->next;
		last->next = new_token;
	}
}
