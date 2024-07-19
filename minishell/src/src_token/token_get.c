/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:14:18 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 14:55:36 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_token_type(t_token **token)
{
	return ((*token)->type);
}

int	get_token_start(t_token **token)
{
	return ((*token)->start);
}

char	*get_token_extract(t_token **token)
{
	return ((*token)->extract);
}

int	get_token_end(t_token **token)
{
	return ((*token)->end);
}

t_token	*get_next_token(t_token **token)
{
	return ((*token)->next);
}
