/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 23:28:39 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:27:04 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_proc(t_proc **proc)
{
	if (proc == NULL)
		return ;
	(*proc)->env = NULL;
	(*proc)->fd_in = STDIN_FILENO;
	(*proc)->fd_out = STDOUT_FILENO;
	(*proc)->cmd = NULL;
	(*proc)->args = NULL;
	(*proc)->in_f = NULL;
	(*proc)->out_f = NULL;
	(*proc)->to_append = 0;
	(*proc)->pipe_next = 0;
	(*proc)->path = NULL;
	(*proc)->n_args = 0;
	(*proc)->exit_value = 0;
}
