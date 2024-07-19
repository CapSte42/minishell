/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_copy_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:37:13 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_str(char *str, char *to_fill)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		to_fill[i] = str[i];
		i++;
	}
}
