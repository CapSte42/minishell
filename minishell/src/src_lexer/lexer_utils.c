/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 07:56:42 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/21 16:53:32 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_exception(int c)
{
	int				i;
	const char		exceptions[] = "\"';()|<>&$*";

	i = 0;
	if (ft_isprint(c) && !ft_isspace(c))
	{
		while (exceptions[i])
		{
			if (c == exceptions[i])
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_is_double_exception(int c, int next_c)
{
	const char	exceptions[] = "|<>&";
	int			i;

	if (c != next_c)
	{
		return (0);
	}
	i = 0;
	while (exceptions[i] != '\0')
	{
		if (c == exceptions[i] && next_c == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
