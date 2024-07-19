/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:48:41 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/03 14:36:41 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(char *input, t_token **token)
{
	if (token == NULL || (*token) == NULL)
		return (1);
	quote_handling(token);
	if (token == NULL || (*token) == NULL)
		return (1);
	merge_near_word(token);
	if (token == NULL || (*token) == NULL)
		return (1);
	if (check_grammatical_rules(*token) == 0)
		return (1);
	(void)input;
	return (0);
}
