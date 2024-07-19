/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:57:48 by tpicchio          #+#    #+#             */
/*   Updated: 2024/05/07 16:42:39 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_top_node	ft_update_value(t_top_node top, t_node node, int i)
{
	top.depth = node.depth;
	top.type = node.type;
	top.pos = i;
	return (top);
}
/*
Primo if:
se il top è un comando e il nodo non è un comando aggiorna il top.

Secondo if:
se il top è un pipe e il nodo è un operatore (; && ||) aggiorna il top.

Terzo if:
se il top è un operatore (|| &&)
	e il nodo è un punto e virgola allora aggiorna il top.
se il nodo ha profondità minore allora aggiorna il top.

Quarto if:
se il top è un punto e virgola e il nodo è un punto e virgola
	con profondità minore allora aggiorna il top.
*/

static t_top_node	ft_update_top(t_top_node top, t_node node,
	int i, t_type logi)
{
	if (top.type == LEAF && (logi == SEMICOLON || logi == OR
			|| logi == AND || logi == PIPE))
	{
		top = ft_update_value(top, node, i);
	}
	else if (top.type == PIPE && (logi == SEMICOLON || logi == OR
			|| logi == AND))
	{
		top = ft_update_value(top, node, i);
	}
	else if ((top.type == OR || top.type == AND)
		&& (logi == SEMICOLON || node.depth < top.depth))
	{
		top = ft_update_value(top, node, i);
	}
	else if (top.type == SEMICOLON && node.depth < top.depth)
	{
		top = ft_update_value(top, node, i);
	}
	return (top);
}
/*
Questa funzione cerca il prossimo nodo da collegare con le priorita':
 ; > || > &&/|| > | > comando
 La logica si vede nella ft_update_max qua sopra.
Prende in input l'albero e l'intervallo di ricerca.
Scorre l'albero da destra verso sinistra, quindi da end fino a start.
*/

t_node	*ft_find_next(t_node *tree, int start, int end)
{
	t_type		logi;
	t_top_node	top;
	int			i;

	top.depth = tree[end].depth;
	top.type = tree[end].type;
	top.pos = end;
	i = end;
	while (i >= start)
	{
		logi = tree[i].type;
		if (tree[i].depth <= top.depth)
		{
			top = ft_update_top(top, tree[i], i, logi);
		}
		i--;
	}
	tree[top.pos].pos = top.pos;
	return (tree + top.pos);
}

static void	ft_null_branch(t_node *branch)
{
	branch->left = NULL;
	branch->right = NULL;
}
/*
Questa funzione collega i nodi dell'albero
in base alla logica dei comandi in modo ricorsivo.
Prende in input un puntatore alla radice dell'albero
e la posizione del nodo corrente.
Cerca il nodo di sinistra e quello di destra tramite
la funzione ft_find_next.
Il calcolo dell'intervallo di ricerca per la ft_find_next
ve lo spiego a voce perchè è un po' complicato.
Se un nodo non è un comando allora richiama se stessa con
la posizione del nodo corrente.
Se un nodo è un comando allora chiama la funzione ft_null_branch
per settare a NULL i nodi di sinistra e destra.
*/

void	ft_link_tree(t_node *branch, int pos)
{
	int	i;

	if (pos == 0)
		return ;
	i = pos - 1;
	while (i > 0 && branch[i].left == NULL && branch[i].parent == NULL)
		i--;
	if (branch[i].type != LEAF)
		i++;
	branch[pos].left = ft_find_next(branch, i, pos - 1);
	branch[pos].left->parent = branch + pos;
	i = pos + 1;
	while (branch[i].data && branch[i].right == NULL
		&& branch[i].parent == NULL)
		i++;
	branch[pos].right = ft_find_next(branch, pos + 1, i - 1);
	branch[pos].right->parent = branch + pos;
	if (branch[pos].left->type != LEAF)
		ft_link_tree(branch, branch[pos].left->pos);
	else
		ft_null_branch(branch[pos].left);
	if (branch[pos].right->type != LEAF)
		ft_link_tree(branch, branch[pos].right->pos);
	else
		ft_null_branch(branch[pos].right);
}
