/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isheredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:24:26 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 18:36:43 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_type	ft_isheredoc(char *token)
{
	if (token[0] == '<' && token[1] == '<')
		return (HERE_DOC);
	return (ft_isappend(token));
}
