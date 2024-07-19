/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:12:55 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Calcolo dello spazio occupato dalle $var una volta espanse */
int	var_count(char *str, t_data **data)
{
	int		i;
	int		count;
	char	**env;

	i = -1;
	count = 0;
	env = (*data)->env;
	while (str[++i])
	{
		if (ft_is_exception(str[i]) && str[i] == '$')
			count += var_value_len(env, &str[i + 1]);
		if (str[i] == 34)
		{
			i++;
			while (str[i] && str[i] != 34)
			{
				if (str[i] == '$')
					count += var_value_len(env, &str[i]);
				i++;
			}
			i++;
		}
	}
	return (count);
}
