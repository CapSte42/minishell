/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:30:55 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Aggiorna la variabile ?= nell'env */
void	set_exit_value(char **env, int exit)
{
	char	*exit_value;

	if (env[STATUS] != NULL)
		free(env[STATUS]);
	else
		return ;
	exit_value = ft_itoa(exit);
	env[STATUS] = ft_strjoin("?=", exit_value);
	free(exit_value);
}
