/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdredout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:23:54 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 02:51:51 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_isappend(char *input)
{
	if (ft_strncmp(input, ">>", 3) == 0)
		return (APPEND);
	return (NONE);
}
