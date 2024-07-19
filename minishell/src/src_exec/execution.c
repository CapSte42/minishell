/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:20:36 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/03 19:36:37 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	ft_free_on_error(t_node *nodo, char *cmd, int exit_val)
{
	ft_free_matrix(&nodo->data->env[HOME]);
	ft_free_tree(nodo);
	if (cmd)
		free(cmd);
	exit(exit_val);
}

void	ft_exec_cmd(t_node *n, int *fd)
{
	char	*cmd;
	int		ret;

	if (n->data->files)
	{
		if (ft_manage_redirect(n->data->files, n->data->env, fd) == -1)
			ft_free_on_error(n, NULL, 1);
		if (g_sigint_received == SIGINT)
			return ;
	}
	if (n->data->args[0] == NULL || n->data->args[0][0] == '\0')
		ft_free_on_error(n, NULL, 0);
	cmd = ft_strdup(n->data->args[0]);
	if (ft_strchr(cmd, '/') == NULL)
		cmd = ft_search_path(cmd, n->data->env);
	ret = ft_is_executable(cmd);
	if (ret != 1)
		ft_free_on_error(n, cmd, ret);
	if (execve(cmd, n->data->args, n->data->env) == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", cmd, strerror(errno));
		ft_free_on_error(n, cmd, 126);
	}
}

static void	ft_check_signal(int status)
{
	if (status == 130)
		g_sigint_received = SIGINT;
	else if (status == 131)
		ft_printf_fd(2, "^\\Quit (core dumped)\n");
}

void	ft_launch_cmd(t_node *nodo)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	g_sigint_received = DEFAULT;
	pid = fork();
	if (pid == 0)
	{
		ft_exec_cmd(nodo, fd);
		if (g_sigint_received == SIGINT)
		{
			ft_destroy_fd(fd);
			ft_free_on_error(nodo, NULL, 130);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_interpret_exit_val(&status);
		set_exit_value(nodo->data->env, status);
		ft_check_signal(status);
		ft_restore_std_io(nodo->data->stdio);
	}
}
