/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:07:28 by smontuor          #+#    #+#             */
/*   Updated: 2024/04/06 16:03:46 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_command_in_path(char *input, char *path_token)
{
	struct stat	statbuf;
	char		fulle_path[4096];
	int			path_exist;
	int			is_regular_file;
	int			is_executable;

	if (ft_strlen(path_token) + 1 + ft_strlen(input) + 1 > 4096)
		return (0);
	ft_strlcpy(fulle_path, path_token, 4096);
	ft_strlcat(fulle_path, "/", 4096);
	ft_strlcat(fulle_path, input, 4096);
	path_exist = (stat(fulle_path, &statbuf) == 0);
	if (!path_exist)
		return (0);
	is_regular_file = S_ISREG(statbuf.st_mode);
	is_executable = (statbuf.st_mode & S_IXUSR);
	if (is_regular_file && is_executable)
		return (1);
	return (0);
}

t_type	ft_iscmd(char *input)
{
	char	*path;
	char	**token;
	int		i;

	path = getenv("PATH");
	if (!path)
		return (NONE);
	token = ft_split(path, ':');
	i = 0;
	while (token && token[i] != NULL)
	{
		if (is_command_in_path(input, token[i]))
		{
			ft_free_n(0, 1, &token);
			return (CMD);
		}
		i++;
	}
	if (token)
		ft_free_n(0, 1, &token);
	return (NONE);
}
