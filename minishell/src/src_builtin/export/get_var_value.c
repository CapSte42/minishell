/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:30:31 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Trovo la variabile che sto cercando di espandere in env.
   Se esiste ritorno il suo valore, altrimenti NULL */
char	*get_var_value(char **env, char *to_check)
{
	int		i;
	char	*name;
	char	*env_name;

	i = 0;
	name = var_name(to_check);
	if (name == NULL)
		return (free(name), NULL);
	while (env[i])
	{
		env_name = var_name(env[i]);
		if (ft_strncmp(env[i], name, biggest_str(env_name, name)) == 0)
		{
			free(name);
			free(env_name);
			if (!ft_strchr(env[i], '='))
				return (NULL);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
		free(env_name);
	}
	free(name);
	return (NULL);
}
