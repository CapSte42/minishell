/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmatrix_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:23:49 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/29 13:30:39 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printmatrix_fd(char **matrix, int fd, int flag)
{
	int	i;

	i = 0;
	if (flag)
		ft_putstr_fd("<--BEGIN-->:\n", fd);
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	if (flag)
		ft_putstr_fd("<---END--->.\n", fd);
	return (i);
}
