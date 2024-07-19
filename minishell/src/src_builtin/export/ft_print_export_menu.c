/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:53:35 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static void	swap_strings(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	sort_env(char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = matrix_len(env);
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
				swap_strings(&env[j], &env[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_name(char *str)
{
	size_t	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (ft_strlen(str) == i)
	{
		name = str;
		ft_printf_fd(1, "%s", name);
	}
	else
	{
		name = ft_substr(str, 0, i);
		ft_printf_fd(1, "%s=", name);
		free(name);
	}
}

void	ft_print_export_menu(char **env, int i)
{
	char	**tmp;

	tmp = copy_env(env);
	sort_env(tmp);
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], "_=", 2) == 0
			|| ft_strncmp(tmp[i], " \0", 2) == 0)
		{
			i++;
			continue ;
		}
		if (ft_strlen(tmp[i]) > 0)
		{
			ft_printf_fd(1, "declare -x ");
			print_name(tmp[i]);
			if (ft_strchr(tmp[i], '='))
				ft_printf_fd(1, "\"%s\"\n", ft_strchr(tmp[i], '=') + 1);
			else
				ft_printf_fd(1, "\n");
		}
		i++;
	}
	ft_free_matrix(tmp);
}
