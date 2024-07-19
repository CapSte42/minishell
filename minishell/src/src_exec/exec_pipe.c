/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:17:36 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 15:40:09 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

static void	ft_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	ft_dup_and_close(int *close_fd, int dup_fd1, int dup_fd2)
{
	dup2(dup_fd1, dup_fd2);
	close(close_fd[0]);
	close(close_fd[1]);
}

static void	ft_child(t_node *nodo, int flag, int *fd, int *stdio_cpy)
{
	int	fd_redir[2];
	int	exit_val_bi;

	if (flag == 0)
		ft_dup_and_close(fd, fd[1], STDOUT_FILENO);
	else
		ft_dup_and_close(fd, stdio_cpy[1], STDOUT_FILENO);
	exit_val_bi = ft_built_ins(nodo);
	if (exit_val_bi >= 0)
	{
		ft_free_matrix(&nodo->data->env[HOME]);
		ft_free_tree(nodo);
		exit(exit_val_bi);
	}
	else if (exit_val_bi == -1)
		ft_exec_cmd(nodo, fd_redir);
	else if (exit_val_bi == -2)
	{
		exit_val_bi = ft_atoi(nodo->data->env[STATUS] + 2);
		ft_free_matrix(&nodo->data->env[HOME]);
		ft_free_tree(nodo);
		exit(exit_val_bi);
	}
}

static void	ft_parent(int flag, int *fd, int *stdio_cpy)
{
	if (flag == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		dup2(stdio_cpy[0], STDIN_FILENO);
		dup2(stdio_cpy[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

pid_t	ft_launch_cmd_pipe(t_node *nodo, int flag, int *stdio_cpy)
{
	pid_t	pid;
	int		fd[2];

	g_sigint_received = DEFAULT;
	if (pipe(fd) == -1)
		ft_error("pipe");
	pid = fork();
	if (pid == -1)
		ft_error("fork");
	if (pid == 0)
		ft_child(nodo, flag, fd, stdio_cpy);
	else
		ft_parent(flag, fd, stdio_cpy);
	return (pid);
}
