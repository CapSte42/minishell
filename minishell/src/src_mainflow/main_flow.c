/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:13:33 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/05 10:36:23 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

static void	preliminary(t_token **token, pid_t *pid, char ***env_copy)
{
	*pid = ft_getpid();
	*env_copy = ft_duplicate_env(pid);
	read_history(NULL);
	*token = NULL;
	setup_signal_handlers();
}

static int	ft_execution_core(t_node **tree, t_token **token,
	char ***env_copy, char **rl)
{
	t_node	*head;
	int		exec_status;

	*tree = token_to_array_tree(token, env_copy, 0, 0);
	free(*rl);
	*rl = NULL;
	free_tokens(token);
	free(*token);
	exec_status = -1;
	if (*tree != NULL)
	{
		head = ft_find_tree_head(*tree);
		ft_link_tree(*tree, head->pos);
		exec_status = ft_exec_tree(head);
		ft_free_tree(*tree);
	}
	return (exec_status);
}

static int	init_main_loop(char **rl, char ***env_copy)
{
	int	stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	g_sigint_received = DEFAULT;
	while (g_sigint_received != SIGINT && *rl == NULL)
	{
		*rl = get_rl();
		if (g_sigint_received == SIGINT || (*rl != NULL && **rl == '\0'))
		{
			dup2(stdin_fd, STDIN_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			if (g_sigint_received == SIGINT)
				set_exit_value(*env_copy, 130);
			else if (*rl != NULL && **rl == '\0')
				set_exit_value(*env_copy, 2);
			*rl = NULL;
		}
		else if (*rl && ft_isspace_all(*rl) == 1)
			ft_free((void **)rl);
		else if (*rl == NULL)
			return (close(stdin_fd), 1);
		g_sigint_received = DEFAULT;
	}
	return (close(stdin_fd), add_history(*rl), write_history(NULL), 0);
}

void	main_loop(char **rl, t_token **token, char ***env_copy)
{
	t_node	*tree;
	int		exec_status;

	exec_status = 0;
	while (1)
	{
		if (init_main_loop(rl, env_copy) == 1)
			break ;
		else if (ft_isspace_all(*rl) == 0)
		{
			lexer(*rl, token);
			if (parser(*rl, token) == 0)
				exec_status = ft_execution_core(&tree, token, env_copy, rl);
			else
			{
				set_exit_value(*env_copy, 2);
				ft_free((void **)rl);
				free_tokens(token);
				free(*token);
			}
		}
		if (exec_status == -2)
			break ;
	}
}

int	main(void)
{
	char	*rl;
	t_token	*token;
	pid_t	pid;
	char	**env;
	int		exit_status;

	rl = NULL;
	preliminary(&token, &pid, &env);
	main_loop(&rl, &token, &env);
	exit_status = ft_atoi((ft_strchr(env[STATUS], '=') + 1));
	ft_free_matrix(&env[HOME]);
	if (token)
		free(token);
	clear_history();
	ft_printf_fd(1, "exit\n");
	close(0);
	close(1);
	return (exit_status);
}
