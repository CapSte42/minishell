/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isparentheses_c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:28:11 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 02:52:32 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_isparenthesis_c(char *input)
{
	if (ft_strncmp(input, ")", 2) == 0)
		return (PARENTHESIS_C);
	return (NONE);
}
