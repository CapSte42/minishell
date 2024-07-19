/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:07:03 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getcwd(void)
{
	size_t	size;
	char	*ret;

	size = 4096;
	ret = ft_calloc(size, sizeof(char));
	while (getcwd(ret, size) == NULL)
	{
		if (errno == ERANGE)
		{
			free(ret);
			size *= 2;
			ret = ft_calloc(size, sizeof(char));
			if (!ret)
			{
				return (print_and_free(&ret,
						"Failed to reallocate memory"));
			}
		}
		else
		{
			return (print_and_free(&ret,
					"Error getting current working directory"));
		}
	}
	return (ret);
}
