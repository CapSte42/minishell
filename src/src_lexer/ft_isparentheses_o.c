/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isparentheses_o.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:26:25 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 02:52:28 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_isparenthesis_o(char *input)
{
	if (ft_strncmp(input, "(", 2) == 0)
		return (PARENTHESIS_O);
	return (NONE);
}
