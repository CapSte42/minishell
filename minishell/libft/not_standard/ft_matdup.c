/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:03:27 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/05 11:03:32 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matdup(char **mat)
{
	char	**new_mat;
	int		i;

	i = 0;
	while (mat[i])
		i++;
	new_mat = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (mat[i])
	{
		new_mat[i] = ft_strdup(mat[i]);
		i++;
	}
	return (new_mat);
}
