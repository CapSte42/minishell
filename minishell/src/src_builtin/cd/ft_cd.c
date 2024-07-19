/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:06:02 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(char **env, char *tmp_pwd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (find_in_env(env, "PWD"))
	{
		tmp = ft_strdup(env[find_in_env(env, "PWD")]);
		while (env[i] && ft_strncmp("OLDPWD", env[i], 6) != 0)
			i++;
		free(env[i]);
		env[i] = ft_strjoin("OLD", tmp);
		free(tmp);
	}
	else
	{
		while (env[i] && ft_strncmp("OLDPWD", env[i], 6) != 0)
			i++;
		free(env[i]);
		env[i] = ft_strjoin("OLDPWD=", tmp_pwd);
	}
}

/* Salvo PWD in OLDPWD e poi riuso getcwd per PWD */
static void	update_pwd(char **env, char *tmp_pwd)
{
	int		i;
	char	*buf;

	i = 0;
	buf = getcwd(NULL, 0);
	if (find_in_env(env, "OLDPWD"))
		update_oldpwd(env, tmp_pwd);
	while (env[i] && ft_strncmp("PWD", env[i], 3) != 0)
		i++;
	if (find_in_env(env, "PWD"))
	{
		free(env[i]);
		env[i] = ft_strjoin("PWD=", buf);
	}
	free(buf);
}

static int	check_and_go(t_data **data, char *print, char *var, char **tmp)
{
	if (find_in_env((*data)->env, var))
	{
		ft_printf_fd(1, "%s\n", get_var_value((*data)->env, var));
		chdir(get_var_value((*data)->env, var));
		update_pwd((*data)->env, *tmp);
		free(*tmp);
		set_exit_value((*data)->env, 0);
		return (0);
	}
	else
	{
		set_exit_value((*data)->env, 1);
		return (print_and_return(tmp, print, NULL));
	}
}

static int	ft_cd_utils(t_data **data, int *fd, char **tmp)
{
	if (ft_strncmp("-\0", (*data)->args[1], 2) == 0)
		return (ft_destroy_fd(fd),
			check_and_go(data, "OLDPWD not set", "OLDPWD", tmp));
	if (chdir((*data)->args[1]) != 0)
	{
		set_exit_value((*data)->env, 1);
		return (ft_destroy_fd(fd),
			print_and_return(tmp, "No such file or directory",
				(*data)->args[1]));
	}
	update_pwd((*data)->env, *tmp);
	free(*tmp);
	return (set_exit_value((*data)->env, 0), 0);
}

/* CD, con update delle relative variabili d'ambiente */
int	ft_cd(t_data **d)
{
	char		*tmp;
	static int	fd[2];

	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	tmp = my_getcwd();
	if (tmp == NULL)
		return (set_exit_value((*d)->env, 1), ft_destroy_fd(fd), 1);
	if (matrix_len((*d)->args) > 2)
		return (ft_destroy_fd(fd),
			print_and_return(&tmp, "too many arguments", NULL),
			set_exit_value((*d)->env, 1), 1);
	if (!(*d)->args[1] || (*d)->args[1] == NULL
		|| ft_strncmp("--\0", (*d)->args[1], 3) == 0)
		return (ft_destroy_fd(fd),
			check_and_go(d, "HOME not set", "HOME", &tmp));
	else if ((*d)->args[1] && ft_strncmp("~\0", (*d)->args[1], 2) == 0)
	{
		update_pwd((*d)->env, *((*d)->env - 3));
		chdir(*((*d)->env - 3));
		return (free(tmp), set_exit_value((*d)->env, 0), 0);
	}
	else
		return (ft_cd_utils(d, fd, &tmp));
}
