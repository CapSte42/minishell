/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:43:06 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/04 14:44:19 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_std_io(int *stdio_copy)
{
	dup2(stdio_copy[0], STDIN_FILENO);
	dup2(stdio_copy[1], STDOUT_FILENO);
}

static char	*check_local_path(char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin("./", cmd);
	if (access(tmp, F_OK) == 0)
	{
		free(cmd);
		cmd = ft_strdup(tmp);
	}
	free(tmp);
	return (cmd);
}

char	*ft_search_path(char *cmd, char **env)
{
	char	**path;
	char	*ret;
	char	*buf;
	int		i;

	buf = ft_strdup(get_var_value(env, "PATH"));
	path = ft_split(buf, ':');
	free(buf);
	if (!path)
		return (cmd);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_freejoin(path[i], "/");
		path[i] = ft_freejoin(path[i], cmd);
		if (access(path[i], F_OK) == 0)
		{
			ret = ft_strdup(path[i]);
			return (ft_free_matrix(path), free(cmd), ret);
		}
	}
	buf = check_local_path(cmd);
	cmd = ft_strdup(buf);
	return (free(buf), ft_free_matrix(path), cmd);
}
