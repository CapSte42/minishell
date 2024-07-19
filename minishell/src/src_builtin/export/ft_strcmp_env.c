/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:46:18 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* strlen modificato per contare la lunghezza del
   nome di una variabile con o senza '=' */
static int	ft_strlen_ext(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}

/* Versione custom di strcmp per controllare se una variabile
   esiste gia' in env, oppure comparare due variabili
   fino al segno '=' o '+', se ce l'hanno.
   Ritorno 1 se non combaciano e 0 se invece esiste gia' */
int	ft_strcmp_env(char *str_env, char *str)
{
	int	i;

	i = 0;
	while ((str_env[i] && str[i]) && str_env[i] != '='
		&& (str[i] != '=' || str[i] != '+'))
	{
		if (str_env[i] - str[i] != 0)
			return (1);
		i++;
	}
	if (ft_strlen_ext(str_env) != ft_strlen_ext(str))
		return (1);
	return (0);
}
