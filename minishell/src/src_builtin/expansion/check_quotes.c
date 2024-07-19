/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:57:19 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Controllo base sul numero di virgolette. 
   Se e' ok ritorno i, altrimenti ritorno zero */
int	check_quotes(char *str, int i)
{
	t_state	state;

	state = INIT;
	while (str[++i])
	{
		if (str[i++] == 34 && state == INIT)
		{
			state = IN_DOUBLE_QUOTE;
			while (str[i] && str[i] != 34)
				i++;
			if (str[i] && str[i] == 34)
				state = INIT;
		}
		if (str[i++] == 39 && state == INIT)
		{
			state = IN_SINGLE_QUOTE;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] && str[i] == 39)
				state = INIT;
		}
		if (state != INIT)
			return (0);
	}
	return (i);
}
