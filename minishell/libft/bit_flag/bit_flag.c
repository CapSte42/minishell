/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:50:29 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 16:05:56 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	bit_flag(char *c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!(*c & (1 << i)))
		{
			*c |= (1 << i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	bit_flag_fd(char *c, int i)
{
	if (i >= 0 && i < 8)
	{
		if (!(*c & (1 << i)))
		{
			*c |= (1 << i);
			return (1);
		}
		return (0);
	}
	else
	{
		return (-1);
	}
}
