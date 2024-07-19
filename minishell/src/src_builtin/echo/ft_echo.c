/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:01:08 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_print(t_data **d, int *i)
{
	while ((*d)->args[*i])
	{
		if (ft_strlen((*d)->args[*i]) == 0)
		{
			ft_printf(" ");
			*i += 1;
			continue ;
		}
		ft_printf("%s", (*d)->args[*i]);
		if ((*d)->args[*i + 1])
			ft_printf(" ");
		*i += 1;
	}
}

static int	ft_flaaaaaaaaaag(char *arg)
{
	int	i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_data **d, int i)
{
	int			flag;
	static int	fd[2];

	flag = 0;
	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (close_fd(fd), set_exit_value((*d)->env, 1), 1);
	if (!(*d)->args[i] || (*d)->args[i] == NULL)
		return (ft_printf_fd(1, "\n"), ft_destroy_fd(fd), 0);
	else
	{
		while ((*d)->args[i] && ft_strncmp((*d)->args[i], "-n", 2) == 0
			&& ft_flaaaaaaaaaag((*d)->args[i]))
		{
			i++;
			flag = 1;
		}
		if ((*d)->args[i]
			&& ft_strncmp((*d)->args[i], "-n\0", 3) == 0 && !(*d)->args[2])
			return (ft_destroy_fd(fd), 0);
		main_print(d, &i);
	}
	if (flag == 0)
		ft_printf_fd(1, "\n");
	return (set_exit_value((*d)->env, 0), ft_destroy_fd(fd), 0);
}
