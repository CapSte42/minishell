/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:21:17 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_env_amount(t_data **data)
{
	int	env_len;
	int	args_len;
	int	to_max;

	env_len = matrix_len((*data)->env);
	args_len = matrix_len((*data)->args);
	to_max = 200 - env_len;
	if (to_max <= 0)
	{
		ft_printf_fd(2, "WARNING. Export failed!\n");
		ft_printf_fd(2, "Maximum amount of variables reached\n");
		return (1);
	}
	if (args_len > to_max)
	{
		ft_printf_fd(2, "WARNING. Export failed!\n");
		ft_printf_fd(2, "Maximum amount of variables exceede.\n");
		ft_printf_fd(2, "Retry. You have %d variable slots left\n", to_max);
		return (1);
	}
	return (0);
}

/* Crea una nuova matrice con le variabili da esportare o aggiornare */
static char	**update_args(t_data **data)
{
	int		i;
	int		j;
	char	**new_args;
	char	*tmp;

	i = 1;
	j = 0;
	new_args = ft_calloc(matrix_len((*data)->args), sizeof(char *));
	while ((*data)->args[i])
	{
		tmp = find_value(&(*data)->args[i], new_args, (*data)->env, 0);
		if (tmp)
		{
			new_args[j] = ft_strdup(tmp);
			j++;
		}
		free(tmp);
		i++;
	}
	new_args[j] = NULL;
	return (new_args);
}

static void	check_and_unset(char **env, char **na)
{
	int		i;
	int		j;
	char	*t;
	char	*t1;

	i = 0;
	j = 0;
	while (na[j])
	{
		t = var_name(na[j]);
		i = 0;
		while (env[i] && env[i] != NULL)
		{
			t1 = var_name(env[i]);
			if (ft_strncmp(t, t1, biggest_str(t, t1)) == 0 && has_value(na[j]))
			{
				free(env[i]);
				env[i] = ft_strdup(" ");
			}
			free(t1);
			i++;
		}
		free(t);
		j++;
	}
}

static int	check_exit_value(t_data **d)
{
	int	i;

	i = 0;
	while ((*d)->args[i])
	{
		if (!check_str((*d)->args[i], (*d)->env, 0, 0))
		{
			set_exit_value((*d)->env, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Da sistemare il valore di ritorno di exit!! */
int	ft_export(t_data **d, int i, int j, int exit_val)
{
	static int	fd[2];
	char		**new_args;

	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	if (!(*d)->args[1])
		return (ft_print_export_menu((*d)->env, 0), ft_destroy_fd(fd), 0);
	if (check_env_amount(d) == 1)
		return (ft_destroy_fd(fd), 1);
	exit_val = check_exit_value(d);
	new_args = update_args(d);
	check_and_unset((*d)->env, new_args);
	while ((*d)->env[j] && (*d)->env[j] != NULL)
	{
		if (ft_strncmp((*d)->env[j], " \0", 2) == 0 && new_args[i] != NULL)
			free_and_copy(d, new_args, &i, &j);
		j++;
	}
	while (new_args[i] && new_args[i] != NULL)
	{
		free_and_copy(d, new_args, &i, &j);
		j++;
	}
	return (ft_free_matrix(new_args), ft_destroy_fd(fd), exit_val);
}
