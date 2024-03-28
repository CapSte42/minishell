/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:07:28 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/11 10:22:00 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum type	ft_iscmd(char *input)
{
	struct stat	statbuf;
	char		*path;
	char		**token;
	char		fullPath[4096]; //TODO
	int			i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NONE);
	token = ft_split(path, ':');
	while (token && token[i] != NULL)
	{
		if (ft_strlen(token[i]) + 1 + ft_strlen(input) + 1 <= 4096)
		{
			ft_strlcpy(fullPath, token[i], 4096);
			ft_strlcat(fullPath, "/", 4096);
			ft_strlcat(fullPath, input, 4096);
			if (stat(fullPath, &statbuf) == 0 && S_ISREG(statbuf.st_mode) && (statbuf.st_mode & S_IXUSR))
			{
				ft_free_n(0, 1, &token);
				return (CMD);
			}
		}
		i++;
	}
	if (token)
		ft_free_n(0, 1, &token);
	return (NONE);
}
