/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_value_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:06:35 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Controllo se la var esiste in env e restituisco la lunghezza del suo valore.
   Se non esiste ritorno zero */
int	var_value_len(char **env, char *to_check)
{
	int		i;
	char	*name;

	i = 0;
	if (!to_check || ft_strlen(to_check) == 0)
		return (0);
	if (ft_strncmp(to_check, "$$", 2) == 0)
		return (ft_strlen(env[PID]) - 2);
	if (ft_strncmp(to_check, "$?", 2) == 0)
		return (ft_strlen(env[STATUS]) - 2);
	name = var_name(to_check);
	while (env[i])
	{
		if (ft_strcmp_env(env[i], name) == 0)
		{
			free(name);
			if (!ft_strchr(env[i], '='))
				return (0);
			return ((int) ft_strlen(ft_strchr(env[i], '=') + 1));
		}
		i++;
	}
	free(name);
	return (0);
}
