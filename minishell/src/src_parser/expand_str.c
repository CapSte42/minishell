/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:15:24 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/03 16:38:11 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reallocate_args(t_data *data, int j)
{
	char	**new_args;
	int		i;
	int		k;
	int		n;

	i = 0;
	k = 0;
	n = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], "```", 3) == 0)
			n++;
		i++;
	}
	new_args = ft_calloc(j - n + 1, sizeof(char *));
	i = 0;
	while (data->args[i])
	{
		if (ft_strncmp(data->args[i], "```", 3) == 0)
			i++;
		else
			new_args[k++] = ft_strdup(data->args[i++]);
	}
	ft_free_matrix(data->args);
	data->args = new_args;
}

static int	ft_surrended(int *flags)
{
	ft_memset(flags, 0, 4096);
	return (-1);
}

int	ft_expand_args(t_data *data, char **env)
{
	int		i;
	int		flags[4096];
	char	*buf;

	i = ft_surrended(flags);
	while (data->args[++i])
	{
		buf = ft_strdup(data->args[i]);
		data->args[i] = var_expansion(env, data->args[i], 0, 0);
		if (ft_strncmp(buf, data->args[i], ft_strlen(data->args[i])) != 0)
			flags[i] = 1;
		else
			flags[i] = 0;
		free(buf);
	}
	data->args = ft_check_wildcard(data);
	i = -1;
	reallocate_args(data, matrix_len(data->args));
	while (data->args[++i])
	{
		data->args[i] = quotes_expansion(data->args[i], -1, 0);
		if (flags[i])
			ft_fix_args(data, i);
	}
	return (0);
}

int	ft_expand_files(t_redir *files, char **env)
{
	t_redir	*tmp;
	char	*tmp2;

	tmp = files;
	while (tmp)
	{
		if (tmp->type != HERE_DOC && tmp->type != HERE_DOC_E)
		{
			tmp2 = var_expansion(env, tmp->name, 0, 0);
			tmp->name = quotes_expansion(tmp2, -1, 0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_check_expand(t_data *leaf)
{
	ft_expand_args(leaf, leaf->env);
	ft_expand_files(leaf->files, leaf->env);
}
