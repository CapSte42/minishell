/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:10:11 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/04 12:40:49 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

static void	update_shlvl(char ***env, int i, int shlvl)
{
	char	*shlvl_str;

	if ((*env)[i])
		free((*env)[i]);
	shlvl_str = ft_itoa(shlvl);
	(*env)[i] = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
}

static int	adjust_shlvl(int shlvl)
{
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl > 998)
	{
		ft_putstr_fd("minishell: warning:", 2);
		ft_putstr_fd(" shell level (1000) too high, resetting to 1\n", 2);
		shlvl = 1;
	}
	else
		shlvl++;
	return (shlvl);
}

static int	get_shlvl(char **env)
{
	int		i;
	int		shlvl;
	char	*shlvl_str;

	i = 0;
	shlvl = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
		{
			shlvl_str = ft_strdup(env[i] + 6);
			shlvl = ft_atoi(shlvl_str);
			free(shlvl_str);
			break ;
		}
		i++;
	}
	return (shlvl);
}

void	set_shlvl(char ***env)
{
	int		i;
	int		shlvl;

	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], "SHLVL=", 6) != 0)
		i++;
	if ((*env)[i] == NULL)
	{
		(*env)[i] = ft_strdup("SHLVL=1");
		(*env)[i + 1] = NULL;
		return ;
	}
	shlvl = get_shlvl(*env);
	shlvl = adjust_shlvl(shlvl);
	update_shlvl(env, i, shlvl);
}

char	**ft_duplicate_env(pid_t *pid)
{
	char	**env_copy;
	char	**env_tmp;
	char	*tmp;
	int		i;

	env_copy = ft_calloc(sizeof(char *), 200);
	if (env_copy == NULL)
		exit(1);
	env_copy[0] = ft_strdup(get_var_value(environ, "HOME"));
	env_copy[1] = ft_calloc(sizeof(char), 10);
	ft_strlcpy(env_copy[1], "?=0\0", 4);
	tmp = ft_itoa(*pid);
	env_copy[2] = ft_strjoin("$=", tmp);
	free(tmp);
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], "LINES=", 6) != 0)
	{
		env_copy[i + 3] = ft_strdup(environ[i]);
		i++;
	}
	env_copy[i + 3] = NULL;
	env_tmp = env_copy + 3;
	set_shlvl(&env_tmp);
	return (env_copy + 3);
}
