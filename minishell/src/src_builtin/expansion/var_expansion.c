/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:34:53 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_single(char *expanded, char *str, int *j, int *i)
{
	int	tmp_i;
	int	tmp_j;

	tmp_i = *i;
	tmp_j = *j;
	expanded[tmp_j++] = str[tmp_i++];
	while (str[tmp_i] != 39)
		expanded[tmp_j++] = str[tmp_i++];
	expanded[tmp_j++] = str[tmp_i++];
	*i = tmp_i;
	*j = tmp_j;
}

static char	*allocate(char **env, char *str)
{
	int		n;
	char	*ret;

	n = var_allocate(str, env) + 2;
	ret = ft_calloc(4096, sizeof(char));
	return (ret);
}

static char	*return_expanded(char *str, t_expand *expand)
{
	if (ft_strlen(expand->expanded) == 0)
	{
		free(expand->expanded);
		expand->expanded = ft_strdup("```");
	}
	return (free(str), expand->expanded);
}

/* Espansione finale di tutte le $var */
char	*var_expansion(char **env, char *str, int i, int j)
{
	t_expand	expand;

	expand = (t_expand){env, str, &i, &j, allocate(env, str), NULL};
	while (str[i])
	{
		if (str[i] == 39 && ft_strchr(&str[i + 1], 39))
			copy_single(expand.expanded, str, &j, &i);
		else if (str[i] == 34 && ft_strchr(&str[i + 1], 34))
		{
			expand.expanded[j++] = str[i++];
			while (str[i] != 34)
			{
				if (str[i] == '$')
					expand_and_copy(&expand, 1);
				else
					expand.expanded[j++] = str[i++];
			}
			expand.expanded[j++] = str[i++];
		}
		else if (str[i] == '$')
			expand_and_copy(&expand, 0);
		else
			expand.expanded[j++] = str[i++];
	}
	return (return_expanded(str, &expand));
}
