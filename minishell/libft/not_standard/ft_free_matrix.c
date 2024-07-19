/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:08:41 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/28 14:24:43 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
	}
	matrix = NULL;
}
