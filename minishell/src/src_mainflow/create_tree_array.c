/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:14:32 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/03 14:38:22 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_sigint_received;

static void	ft_init_vars(t_node **tree, t_token **token, t_token **tmp)
{
	int		size;

	size = count_operators(*token);
	*tree = ft_calloc(sizeof(t_node), size);
	if (*tree == NULL)
		exit(1);
	(*tree)[size - 1].data = NULL;
	(*tree)[size - 1].type = END;
	*tmp = *token;
}

static int	ft_init_node(t_node *node, t_token *tmp,
	char ***env_copy, int depth)
{
	if (tmp->exception != 1)
		node->type = LEAF;
	else
		node->type = tmp->type;
	node->depth = depth;
	node->pos = 0;
	node->data = ft_calloc(sizeof(t_data), 1);
	if (node->data == NULL)
		return (1);
	node->data->env = *env_copy;
	node->data->args = NULL;
	node->data->files = NULL;
	node->data->stdio[0] = dup(STDIN_FILENO);
	node->data->stdio[1] = dup(STDOUT_FILENO);
	return (0);
}

static int	ft_manage_leaf(t_node *node, t_token **tmp)
{
	t_token	*head;

	head = *tmp;
	node->data->files = ft_create_list_files(tmp);
	node->data->args = ft_create_args(head);
	ft_priority_heredoc(node->data->files);
	if (g_sigint_received == SIGINT)
	{
		dup2(node->data->stdio[0], STDIN_FILENO);
		set_exit_value(node->data->env, 130);
		ft_free_tree(node);
		g_sigint_received = DEFAULT;
		return (1);
	}
	return (0);
}

t_node	*token_to_array_tree(t_token **token,
	char ***env_copy, int i, int depth)
{
	t_node	*tree;
	t_token	*tmp;

	ft_init_vars(&tree, token, &tmp);
	while (tmp)
	{
		if ((tmp->type == PARENTHESIS_O && ++depth >= 0)
			|| (tmp->type == PARENTHESIS_C && --depth >= 0))
			tmp = skip_space_tokens(tmp->next);
		else
		{
			ft_init_node(&tree[i], tmp, env_copy, depth);
			if (tmp->exception != 1)
			{
				if (ft_manage_leaf(&tree[i], &tmp) == 1)
					return (NULL);
			}
			else
				tmp = skip_space_tokens(tmp->next);
			i++;
		}
	}
	return (tree);
}
