/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:56:14 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_isfile(char *input)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd != -1)//TODO check permessi
	{
		close(fd);
		return (MY_FILE);
	}
	return (NONE);
}
