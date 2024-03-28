/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:52:59 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_issquote(char *input)
{
	if (ft_strncmp(input, "'", 2) == 0)
		return (S_QUOTE);
	return (NONE);
}
