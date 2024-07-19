/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:24:54 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/01 11:43:54 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

static int	clean_hd(t_redir *tmp, char *limiter, char *line)
{
	free(limiter);
	free(line);
	if (tmp->name == NULL)
		tmp->name = ft_strdup("");
	ft_get_next_line(-42);
	return (1);
}

static int	ft_check_line(char *line, char *limiter)
{
	if (line == NULL)
	{
		ft_printf_fd(2, "minishell: warning: here_doc ");
		ft_printf_fd(2, "terminated with EOF (wanted `%s')\n", limiter);
		return (1);
	}
	if (!ft_strncmp(line, limiter, ft_strlen(limiter))
		&& line[ft_strlen(limiter)] == '\n')
		return (1);
	return (0);
}

static int	heredoc_color(int color)
{
	if (color == 0)
	{
		color = 31;
	}
	else if (color < 37)
	{
		color++;
	}
	else
	{
		color = 30;
	}
	return (color);
}

static void	ft_initial_setup(t_redir **tmp, char **limiter, int *color)
{
	g_sigint_received = DEFAULT;
	*color = heredoc_color(*color);
	if (ft_strchr((*tmp)->name, '"') == 0 && ft_strchr((*tmp)->name, '\'') == 0)
		(*tmp)->type = HERE_DOC_E;
	*limiter = ft_strdup((*tmp)->name);
	*limiter = quotes_expansion(*limiter, -1, 0);
	free((*tmp)->name);
	(*tmp)->name = NULL;
}

void	ft_priority_heredoc(t_redir *files)
{
	static int	color = 0;
	t_redir		*tmp;
	char		*line;
	char		*lim;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			ft_initial_setup(&tmp, &lim, &color);
			while (1)
			{
				ft_printf_fd(1, "\033[1;%dmhere_doc: %s\033[0m> ", color, lim);
				line = ft_get_next_line(0);
				if (g_sigint_received == SIGINT && clean_hd(tmp, lim, line))
					return ;
				if (ft_check_line(line, lim))
					break ;
				tmp->name = ft_brojoin(tmp->name, line);
			}
			clean_hd(tmp, lim, line);
		}
		tmp = tmp->next;
	}
}
