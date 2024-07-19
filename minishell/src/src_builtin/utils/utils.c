/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:44:09 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_ins(t_node *nodo)
{
	if (nodo->data->args[0] == NULL)
		return (-1);
	if (ft_strncmp(nodo->data->args[0], "pwd\0", 4) == 0)
		return (ft_pwd(&(nodo->data)));
	else if (ft_strncmp(nodo->data->args[0], "env\0", 4) == 0)
		return (ft_env(&(nodo->data)));
	else if (ft_strncmp(nodo->data->args[0], "echo\0", 5) == 0)
		return (ft_echo(&(nodo->data), 1));
	else if (ft_strncmp(nodo->data->args[0], "export\0", 7) == 0)
		return (ft_export(&(nodo->data), 0, 0, 0));
	else if (ft_strncmp(nodo->data->args[0], "unset\0", 6) == 0)
		return (ft_unset(&(nodo->data)));
	else if (ft_strncmp(nodo->data->args[0], "cd\0", 3) == 0)
		return (ft_cd(&(nodo->data)));
	else if (ft_strncmp(nodo->data->args[0], "exit\0", 5) == 0)
		return (ft_exit(&(nodo->data)));
	return (-1);
}

void	ft_destroy_fd(int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 0)
		close(fd[1]);
}
