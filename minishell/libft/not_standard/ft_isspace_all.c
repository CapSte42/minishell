/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:04:11 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/04 19:22:51 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace_all(char *str)
{
	int	i;
	int	tot_spaces;

	i = 0;
	tot_spaces = 0;
	while (str[i] && str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
			tot_spaces++;
		i++;
	}
	if (i == tot_spaces)
		return (1);
	return (0);
}
