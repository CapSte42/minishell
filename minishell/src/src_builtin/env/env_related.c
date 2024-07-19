/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_related.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:30:00 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Funzione per inizializzare le variabili di ambiente con allocazione */
char	**init_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = ft_calloc(201, sizeof(char *));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	has_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/*  ENV */
int	ft_env(t_data **d)
{
	int			i;
	static int	fd[2];

	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	i = 0;
	if (!(*d)->env)
		return (ft_destroy_fd(fd), ft_printf_fd(2, "minishell: NO ENV\n"), 0);
	if ((*d)->args[1])
	{
		ft_printf_fd(2, "minishell: env: %s: No such file or directory\n",
			(*d)->args[1]);
		set_exit_value((*d)->env, 127);
		return (ft_destroy_fd(fd), 127);
	}
	while ((*d)->env[i])
	{
		if (has_value((*d)->env[i]) && (*d)->env[i][0] != '?')
			ft_printf_fd(1, "%s\n", (*d)->env[i]);
		i++;
	}
	set_exit_value((*d)->env, 0);
	return (ft_destroy_fd(fd), 0);
}
