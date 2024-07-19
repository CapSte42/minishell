/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:59:23 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static void	print_and_set(char *arg, int exit, t_data **data)
{
	if (arg == NULL)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		set_exit_value((*data)->env, 1);
		return ;
	}
	else
		ft_printf_fd(2, "exit: %s: numeric argument required\n", arg);
	set_exit_value((*data)->env, exit);
}

static char	*trim_n(char *str, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

/* EXIT per uscire ritornare -2 */
int	ft_exit(t_data **d)
{
	static int	fd[2];

	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	if (matrix_len((*d)->args) == 1)
		return (ft_destroy_fd(fd), -2);
	if (matrix_len((*d)->args) == 2 && is_digit_exit(*((*d)->args + 1)))
	{
		if (trim_n(*((*d)->args + 1), 1) == NULL)
			return (set_exit_value((*d)->env, 0), -2);
		if (ft_atoll(trim_n(*((*d)->args + 1), 42)) == 0)
		{
			print_and_set(trim_n(*((*d)->args + 1), 42), 2, d);
			return (ft_destroy_fd(fd), -2);
		}
		return (ft_destroy_fd(fd), set_exit_value((*d)->env,
				(unsigned char)ft_atoll(trim_n(*((*d)->args + 1), 42))), -2);
	}
	else if (matrix_len((*d)->args) > 2
		&& (is_digit_exit(trim_n(*((*d)->args + 1), 42))
			|| *((*d)->args + 1)[0] == '0'))
		return (print_and_set(NULL, 2, d), 0);
	else
		return (print_and_set(trim_n(*((*d)->args + 1), 42), 2, d), -2);
}
