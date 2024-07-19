/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:11:20 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/01 11:25:15 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int	count_operators(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->exception == 1)
			count++;
		token = token->next;
	}
	return (count * 2 + 2);
}

void	ft_delete_token_file(t_token **tmp)
{
	(*tmp)->type = TO_JUMP;
	(*tmp) = skip_space_tokens((*tmp)->next);
	(*tmp)->type = TO_JUMP;
	(*tmp) = skip_space_tokens((*tmp)->next);
}

static int	conditions(t_token *tmp, int flag)
{
	if (flag == 0)
		return (tmp && tmp->exception != 1 && tmp->type != PARENTHESIS_C);
	else
		return (tmp->type != TO_JUMP && tmp->type
			!= SSPACE && tmp->type != PARENTHESIS_O);
}

int	ft_count_args(t_token *tmp)
{
	int	count;

	count = 0;
	while (conditions(tmp, 0))
	{
		if (tmp->type != TO_JUMP && tmp->type != SSPACE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**ft_create_args(t_token *tmp)
{
	char	**args;
	int		i;

	args = ft_calloc(sizeof(char *), ft_count_args(tmp) + 1);
	if (args == NULL)
		return (NULL);
	i = 0;
	while (conditions(tmp, 0))
	{
		if (conditions(tmp, 1))
		{
			args[i] = ft_strdup(tmp->extract);
			i++;
		}
		tmp = skip_space_tokens(tmp->next);
	}
	args[i] = NULL;
	return (args);
}
