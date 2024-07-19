/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 22:55:03 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 15:06:03 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	ft_isdir(char *input)
{
	DIR	*dir;

	dir = opendir(input);
	if (dir)
	{
		closedir(dir);
		return (DIRECTORY);
	}
	return (NONE);
}
