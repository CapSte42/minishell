/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:36:47 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:37:29 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

static char	*ft_get_working_dir(char *str)
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		ft_printf_fd(2, "minishell: error retrieving working directory\n");
	tmp = ft_strrchr(cwd, '/');
	if (tmp == NULL)
		ft_printf_fd(2, "minishell: error retrieving working directory\n");
	prompt = ft_strjoin(str, tmp);
	prompt = ft_freejoin(prompt, WHITE"$ "RESET);
	free(cwd);
	return (prompt);
}

char	*get_rl(void)
{
	char	*tmp;
	char	*prompt;
	t_state	quote_state;
	t_state	paren_state;
	t_type	type;

	prompt = ft_get_working_dir(YELLOW"minishell"WHITE":"BLUE"..");
	tmp = readline(prompt);
	free(prompt);
	if (g_sigint_received == SIGINT)
		return (NULL);
	while (tmp != NULL && is_unbalanced(tmp, &quote_state, &paren_state, &type))
	{
		g_sigint_received = DEFAULT;
		if (quote_state != INIT)
			tmp = handle_input(tmp, 1, 0);
		if (is_continuation_token(type) && (quote_state + paren_state == 0))
			tmp = handle_input(tmp, 2, 0);
		if (paren_state != INIT && quote_state == INIT)
			tmp = handle_input(tmp, 3, (paren_state == 6));
		if (g_sigint_received == SIGINT)
			return (NULL);
	}
	return (tmp);
}
