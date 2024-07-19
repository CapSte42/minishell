/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:56:14 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 15:06:17 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_isfile(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (MY_FILE);
	}
	return (NONE);
}
