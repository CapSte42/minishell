/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:21:32 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Ritorna 0 se la stringa contiene altro oltre a numeri. 
   Proteggo i caratteri '+' e '-' */
/* TMP && (str[i] == '+' || str[i] == '-') */
int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}

/* Ritorno i se il numero e' un numero valido, altrimenti 0 */
int	is_digit_exit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i);
}
