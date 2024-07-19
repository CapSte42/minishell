/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:20:17 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_double(char **args, char *str, int index)
{
	while (index > 0)
	{
		if (ft_strncmp(str, args[index], biggest_str(str, args[index])) == 0)
			return (1);
		index--;
	}
	return (0);
}

static int	check_name(char *env, char **args)
{
	int	i;

	i = 1;
	if (!env)
		return (1);
	while (args[i])
	{
		if (ft_strcmp_env(env, args[i]) == 0
			&& !is_double(args, args[i], i - 1))
			return (0);
		i++;
	}
	return (1);
}

static void	update_args(t_data **d, int *exit)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = ft_calloc(matrix_len((*d)->args) + 1, sizeof(char *));
	while ((*d)->args[++i])
	{
		if (ft_strchr((*d)->args[i], '='))
		{
			tmp[j++] = ft_strdup("!!!");
			*exit = 1;
			ft_printf_fd(2, "%s : not a valid identifier\n", (*d)->args[i]);
		}
		else if (!check_str((*d)->args[i], (*d)->args, 0, 1))
		{
			tmp[j++] = ft_strdup("!!!");
			*exit = 1;
		}
		else
			tmp[j++] = ft_strdup((*d)->args[i]);
	}
	ft_free_matrix((*d)->args);
	(*d)->args = tmp;
}

int	ft_unset(t_data **d)
{
	int			i;
	int			exit;
	static int	fd[2];

	i = 0;
	exit = 0;
	update_args(d, &exit);
	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	if (matrix_len((*d)->args) == 1)
	{
		set_exit_value((*d)->env, 0);
		return (ft_destroy_fd(fd), 0);
	}
	while ((*d)->env[i] && (*d)->env[i] != NULL)
	{
		if (!check_name((*d)->env[i], (*d)->args))
		{
			free((*d)->env[i]);
			(*d)->env[i] = ft_strdup(" ");
		}
		i++;
	}
	return (set_exit_value((*d)->env, exit), ft_destroy_fd(fd), exit);
}
