/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:15:54 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 04:20:57 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t sigint_received = 0;

static void clean_line(char **line)
{
	if (!(*line == NULL))
		free(*line);
	*line = ft_calloc(1, 1);
	if (*line == NULL)
		exit(1); //TODO handle error
}

static void	preliminary_actions(int ac, char **av, t_proc **node)
{
	(void)ac;
	(void)av;
	load_history();
	*node = malloc(sizeof(t_proc));
	if (*node == NULL)
		exit(1); //TODO handle error
	//init_node(node);
	setup_signal_handlers();
}

void	main_loop(t_proc **node, char **rl, char **line)
{
	(void)node;
	while (1)
	{
		if (sigint_received == 1)
			sigint_received = 0;
		clean_line(&(*line));
		*rl = readline("\001\033[1;34m\002minishell\001\033[0m\002$ ");
		my_add_history(*rl);
		if (*rl == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strncmp(*rl, "exit\0", 5) == 0)
		{
			printf("exit\n");
			break;
		}
		if (ft_isspace_all(*rl) == 0)
		{
			lexer(*rl, &(*line));
		}
		free(*rl);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_proc	*proc;
	char	*rl;
	char	*line;

	line = NULL;
	preliminary_actions(ac, av, &proc);
	main_loop(&proc, &rl, &line);
	printf("env: %s\n", envp[0]);
	free(proc);
	free(line);
	return (0);
}
