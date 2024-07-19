/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_con_return.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:30:37 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	ft_refactor_w_command(t_wildcard *w, char **args, int index[3])
{
	while (w->entry != NULL)
	{
		if (ft_strncmp(w->entry->d_name, ".\0", 2) == 0
			|| ft_strncmp(w->entry->d_name, "..\0", 3) == 0)
		{
			w->entry = readdir(w->dir);
			continue ;
		}
		if (args[0] == NULL)
			args[0] = ft_strdup(w->entry->d_name);
		else
			args[index[0]++] = ft_strdup(w->entry->d_name);
		w->entry = readdir(w->dir);
	}
}

static void	ft_reopen(t_wildcard *w)
{
	closedir(w->dir);
	w->dir = opendir(".");
	w->entry = readdir(w->dir);
}

static int	ft_wild_command(t_data *data)
{
	t_wildcard	w;
	int			index[3];
	int			n_args;
	char		**args;

	if (data->args[0] && ft_strncmp(data->args[0], "*\0", 2) == 0)
	{
		ft_init_index(index);
		w.dir = opendir(".");
		if (w.dir == NULL)
			return (0);
		n_args = (int)ft_args_len(data->args);
		args = ft_calloc(ft_files_in_dir(w.dir) + n_args, sizeof(char *));
		ft_reopen(&w);
		ft_refactor_w_command(&w, args, index);
		while (index[1] < n_args)
			args[index[0]++] = ft_strdup(data->args[index[1]++]);
		ft_free_matrix(data->args);
		data->args = args;
		closedir(w.dir);
		free(w.entry);
		return (1);
	}
	return (0);
}

static char	**ft_wild_argument(t_data *data)
{
	char		**args;
	int			indexes[3];
	t_wildcard	w;

	ft_init_index(indexes);
	args = calloc(args_num(data) + 1, sizeof(char *));
	if (args[0] == NULL)
		args[0] = ft_strdup(data->args[0]);
	ft_refactor_wild_arg(data, args, indexes, &w);
	if (ft_args_len(args) >= ft_args_len(data->args))
	{
		ft_free_matrix(data->args);
		return (args);
	}
	if (args != NULL)
		ft_free_matrix(args);
	return (data->args);
}

char	**ft_check_wildcard(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
	{
		if (is_wildcard_unquoted(data->args[i]))
		{
			if (ft_wild_command(data))
				return (data->args);
			return (ft_wild_argument(data));
		}
		i++;
	}
	return (data->args);
}
