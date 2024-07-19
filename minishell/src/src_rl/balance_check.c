/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:38:30 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/01 15:26:06 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unbalanced(char *tmp, t_state *quote_state, t_state *paren_state,
		t_type *type)
{
	*quote_state = check_quote_balance(tmp);
	*paren_state = check_paren_balance(tmp);
	*type = ft_get_last_token_type(tmp);
	return (*quote_state != INIT || (*paren_state != INIT
			&& *paren_state != ERROR) || is_continuation_token(*type)
		|| *paren_state == 6);
}
