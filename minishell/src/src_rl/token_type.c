/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:40:13 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/16 20:47:54 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_get_last_token_type(char *rl)
{
	int		i;
	char	*tmp;
	t_type	type;
	int		len;

	len = 1;
	i = ft_strlen(rl) - 1;
	while (i >= 0 && ft_isspace(rl[i]))
		i--;
	if (i < 0)
		return (NONE);
	if (i > 0)
	{
		if (rl[i] == rl[i - 1] && (((rl[i] == '|') + (rl[i] == '&') == 1)))
		{
			len = 2;
			i--;
		}
	}
	tmp = ft_substr(rl, i, len);
	type = ft_get_token_type(tmp);
	free(tmp);
	return (type);
}

int	is_continuation_token(t_type type)
{
	return (type == AND || type == OR || type == PIPE || type == SEMICOLON);
}
