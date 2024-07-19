/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:32 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:47:02 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type	is_special_token(char *token)
{
	if (!token || token[0] == '\0')
		return (NONE);
	if (token[0] == ' ')
		return (SSPACE);
	if (token[0] == '&')
		return (WORD);
	return (token[0]);
}

static t_type	is_double_special_token(char *token)
{
	if (!token || token[0] == '\0')
		return (NONE);
	return (ft_isand(token));
}

t_type	ft_get_token_type(char *token)
{
	const char	*token_list;
	int			i;

	if (token == NULL || *token == '\0')
		return (NONE);
	i = 0;
	token_list = "\"&()|'<>;$* ";
	while (token_list[i])
	{
		if (token[0] == token_list[i])
		{
			if (!token[1])
				return (is_special_token(token));
			else
				return (is_double_special_token(token));
		}
		i++;
	}
	if (ft_isprint(token[0]))
	{
		return (WORD);
	}
	return (NONE);
}

void	lexer(char *input, t_token **token_list)
{
	int		i;
	int		start;
	int		end;
	char	*token;

	i = 0;
	while (input[i])
	{
		start = i;
		while (ft_is_exception(input[i]) && input[i])
			i++;
		if (start == i && ft_is_double_exception(input[i], input[i + 1]))
		{
			i = i + 2;
		}
		if (start == i)
			i++;
		end = i;
		token = ft_substr(input, start, end - start);
		if (token[0] != '\0')
			add_token(token_list, ft_get_token_type(token), start, token);
	}
}
