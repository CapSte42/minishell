/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:41:22 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_refactor_check(t_wildcard *w, int index[3],
	char **args, t_data *data)
{
	if (check_wildcard(w->to_append, data->args[index[1]]))
	{
		if (args != NULL)
		{
			free(args[index[0]]);
			args[index[0]] = ft_strdup(w->to_append);
		}
		index[0]++;
		index[2] = 1;
	}
}

static void	ft_core(t_data *data, char **args, int index[3], t_wildcard *w)
{
	w->entry = readdir(w->dir);
	while (w->entry != NULL)
	{
		if (ft_strncmp(w->entry->d_name, ".\0", 2) == 0
			|| ft_strncmp(w->entry->d_name, "..\0", 3) == 0)
		{
			w->entry = readdir(w->dir);
			continue ;
		}
		if (strncmp(w->dir_path, ".\0", 2) != 0)
			w->to_append = ft_strjoin(w->dir_path, w->entry->d_name);
		else
			w->to_append = ft_strdup(w->entry->d_name);
		if (data->args[index[1]][ft_strlen(data->args[index[1]]) - 1] == '/'
			&& w->entry->d_type == DT_DIR)
			w->to_append = ft_freejoin(w->to_append, "/");
		ft_refactor_check(w, index, args, data);
		if (w->to_append)
			free(w->to_append);
		w->entry = readdir(w->dir);
	}
}

int	ft_refactor_wild_arg(t_data *data, char **args, int i[3], t_wildcard *w)
{
	while (data->args[i[1]])
	{
		w->dir_path = get_dir_path(ft_strdup(data->args[i[1]]));
		w->dir = opendir(w->dir_path);
		if (w->dir == NULL)
			return (ft_free((void **)&w->dir_path), i[0]);
		if (args)
			args[i[0]] = ft_strdup(data->args[i[1]]);
		if (data->args[i[1]] && ft_strchr(data->args[i[1]], '*') != NULL)
		{
			i[2] = 0;
			ft_core(data, args, i, w);
			closedir(w->dir);
			if (i[2] == 1)
				i[0]--;
		}
		else
			closedir(w->dir);
		i[0]++;
		ft_free((void **)&w->dir_path);
		i[1]++;
	}
	return (i[0]);
}

void	ft_init_index(int index[3])
{
	index[0] = 1;
	index[1] = 1;
	index[2] = 0;
}
