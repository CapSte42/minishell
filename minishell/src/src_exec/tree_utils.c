/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:49:36 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/01 10:33:52 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_find_tree_head(t_node *tree)
{
	t_node	*head;
	int		size;

	size = ft_tree_size(tree);
	size--;
	head = ft_find_next(tree, 0, size);
	head->parent = NULL;
	return (head);
}

int	ft_tree_size(t_node *tree)
{
	int	i;

	i = 0;
	while (tree[i].data)
		i++;
	return (i);
}

void	ft_free_redir_list(t_redir *files)
{
	t_redir	*tmp;

	while (files)
	{
		tmp = files->next;
		if (files->type == HERE_DOC)
			unlink(".here_doc");
		if (files->name)
			free(files->name);
		free(files);
		files = tmp;
	}
	files = NULL;
}

void	ft_free_tree(t_node *node)
{
	t_node	*start;
	int		i;

	start = node;
	while (start->parent)
		start = start->parent;
	while (start->left)
		start = start->left;
	i = 0;
	while (start[i].data)
	{
		ft_free_redir_list(start[i].data->files);
		ft_free_matrix(start[i].data->args);
		close(start[i].data->stdio[0]);
		close(start[i].data->stdio[1]);
		free(start[i].data);
		i++;
	}
	free(start);
}
