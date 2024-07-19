/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:00:11 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/01 11:41:50 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

static void	ft_manage_operator(t_node *nodo)
{
	if (nodo->type == OR)
	{
		if (ft_atoi((ft_strchr(nodo->data->env[-2], '=') + 1)) != 0)
			ft_exec_tree(nodo->right);
	}
	else if (nodo->type == AND)
	{
		if (ft_atoi((ft_strchr(nodo->data->env[-2], '=') + 1)) == 0)
			ft_exec_tree(nodo->right);
	}
	else if (nodo->type == SEMICOLON)
	{
		ft_exec_tree(nodo->right);
	}
}

static void	ft_wait_processes(int num_wait, pid_t last_cmd, char **env)
{
	int	status;
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (i < num_wait)
	{
		if (wait(&status) == last_cmd)
		{
			ft_interpret_exit_val(&status);
			set_exit_value(env, status);
		}
		if (status == 131 && flag == 0)
		{
			ft_printf_fd(2, "^\\Quit (core dumped)\n");
			flag = 1;
		}
		i++;
	}
}

static void	ft_exec_pipe(t_node *nodo, t_node *last_cmd)
{
	pid_t	pid;
	int		i;
	int		cmd;

	cmd = 0;
	i = -1;
	while (nodo->left)
		nodo = nodo->left;
	while (nodo[++i].data)
	{
		if (nodo[i].type != PIPE)
		{
			ft_check_expand(nodo[i].data);
			if (nodo[i + 1].data == NULL
				|| (nodo[i + 1].type != LEAF && nodo[i + 1].type != PIPE))
				pid = ft_launch_cmd_pipe(nodo + i, 1, nodo[i].data->stdio);
			else
				ft_launch_cmd_pipe(nodo + i, 0, nodo[i].data->stdio);
			cmd++;
			if (&nodo[i] == last_cmd)
				break ;
		}
	}
	ft_wait_processes(cmd, pid, nodo->data->env);
	dup2(nodo->data->stdio[0], 0);
}

static int	ft_exec_leaf(t_node *nodo)
{
	int	exit_val_bi;

	if (g_sigint_received == SIGINT)
		return (130);
	ft_check_expand(nodo->data);
	exit_val_bi = ft_built_ins(nodo);
	if (exit_val_bi >= 0)
	{
		dup2(nodo->data->stdio[0], 0);
		dup2(nodo->data->stdio[1], 1);
		if (g_sigint_received == SIGINT)
			return (set_exit_value(nodo->data->env, 130), 130);
		return (0);
	}
	else if (exit_val_bi == -1)
	{
		ft_launch_cmd(nodo);
		if (g_sigint_received == SIGINT)
			return (130);
	}
	else if (exit_val_bi == -2)
		return (exit_val_bi);
	return (0);
}

int	ft_exec_tree(t_node *nodo)
{
	if (nodo == NULL)
		return (0);
	if (nodo->type == PIPE)
		ft_exec_pipe(nodo, nodo->right);
	else
	{
		ft_exec_tree(nodo->left);
		if (nodo->type == LEAF)
		{
			return (ft_exec_leaf(nodo));
		}
		else if (nodo->type == OR
			|| nodo->type == AND || nodo->type == SEMICOLON)
			ft_manage_operator(nodo);
	}
	return (0);
}
