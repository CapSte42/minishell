/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issemicolon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:25:59 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 02:52:45 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_issemicolon(char *input)
{
	if (ft_strncmp(input, ";", 2) == 0)
		return (SEMICOLON);
	return (NONE);
}
