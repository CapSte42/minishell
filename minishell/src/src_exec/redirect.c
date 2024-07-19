/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:11:48 by tpicchio          #+#    #+#             */
/*   Updated: 2024/05/29 16:10:18 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open(char *file, int flags, int permis)
{
	int	fd;

	fd = open(file, flags, permis);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	return (fd);
}

static void	ft_heredoc(char *content, t_type type, char **env, int *fd)
{
	*fd = ft_open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type == HERE_DOC_E && *content)
	{
		content = var_expansion(env, ft_strdup(content), 0, 0);
		ft_printf_fd(*fd, "%s", content);
		free(content);
	}
	else
		ft_printf_fd(*fd, "%s", content);
	close(*fd);
	*fd = ft_open(".here_doc", O_RDONLY, 0644);
}

static int	ft_manage_next(t_redir *files, int *fd)
{
	if (fd[0] < 0 || fd[1] < 0)
		return (-1);
	if (files->next)
	{
		if ((files->next->type == RED_IN
				|| files->next->type == HERE_DOC) && fd[0])
			close(fd[0]);
		if ((files->next->type == RED_OUT
				|| files->next->type == APPEND) && fd[1])
			close(fd[1]);
	}
	return (0);
}

int	ft_manage_redirect(t_redir *files, char **env, int *fd)
{
	fd[0] = 0;
	fd[1] = 0;
	while (files)
	{
		if (files->type == RED_IN)
			fd[0] = ft_open(files->name, O_RDONLY, 0644);
		else if (files->type == RED_OUT)
			fd[1] = ft_open(files->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (files->type == APPEND)
			fd[1] = ft_open(files->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (files->type == HERE_DOC || files->type == HERE_DOC_E)
			ft_heredoc(files->name, files->type, env, &fd[0]);
		if (ft_manage_next(files, fd) == -1)
			return (-1);
		files = files->next;
	}
	if (fd[0])
		dup2(fd[0], 0);
	if (fd[1])
		dup2(fd[1], 1);
	return (0);
}
