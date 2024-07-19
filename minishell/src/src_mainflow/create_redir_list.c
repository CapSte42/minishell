/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:24:28 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/01 11:27:19 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir_node(t_redir **lst_head, t_redir **lst_iter,
	t_token **tmp)
{
	t_redir	*new_node;

	new_node = ft_calloc(sizeof(t_redir), 1);
	if (new_node == NULL)
		exit(1);
	new_node->type = (*tmp)->type;
	(*tmp)->type = TO_JUMP;
	*tmp = skip_space_tokens((*tmp)->next);
	new_node->name = ft_strdup((*tmp)->extract);
	(*tmp)->type = TO_JUMP;
	*tmp = skip_space_tokens((*tmp)->next);
	new_node->next = NULL;
	if (*lst_head == NULL)
	{
		*lst_head = new_node;
		*lst_iter = new_node;
	}
	else
	{
		(*lst_iter)->next = new_node;
		*lst_iter = new_node;
	}
}

t_redir	*ft_create_list_files(t_token **tmp)
{
	t_redir	*lst_head;
	t_redir	*lst_iter;
	t_token	*head;

	lst_head = NULL;
	lst_iter = NULL;
	head = *tmp;
	while (*tmp && (*tmp)->exception != 1 && (*tmp)->type != PARENTHESIS_C)
	{
		if ((*tmp)->exception != 2)
			*tmp = (*tmp)->next;
		else
			add_redir_node(&lst_head, &lst_iter, tmp);
	}
	tmp = &head;
	return (lst_head);
}
