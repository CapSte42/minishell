/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:28:04 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cerco se ci sono += per capire cosa fare col valore della variabile.
   Ritorno 1 se trovo +=, altrimenti 0. */
static int	to_concatenate(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] && str[i] != '+' && str[i + 1] != '=')
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
		return (1);
	else
		return (0);
}

/* Controlla se to_check e' gia' presente nella nuova matrice di args.
   Se si ritorna 1, altrimenti 0 */
static int	already_present(char **new_args, char *to_check)
{
	int		i;
	char	*name_args;
	char	*name_to_check;

	i = 0;
	name_to_check = var_name(to_check);
	if (*new_args == NULL)
		return (free(name_to_check), 0);
	while (new_args[i])
	{
		name_args = var_name(new_args[i]);
		if (ft_strncmp(name_args, name_to_check,
				biggest_str(name_args, name_to_check)) == 0)
		{
			free(name_args);
			free(name_to_check);
			return (1);
		}
		free(name_args);
		i++;
	}
	free(name_to_check);
	return (0);
}

static void	create_str(char **args, char **ret)
{
	if (to_concatenate(*args) && ft_strchr(*ret, '='))
		*ret = ft_freejoin(*ret, ft_strchr(*args, '=') + 1);
	else if (to_concatenate(*args) && !ft_strchr(*ret, '='))
		*ret = ft_freejoin(*ret, ft_strchr(*args, '='));
	if (!to_concatenate(*args) && ft_strchr(*args, '='))
	{
		free(*ret);
		*ret = ft_strdup(*args);
	}
}

/* Funzione che ritorna la variabile finale
   da esportare dopo aver fatto tutti i check */
char	*find_value(char **args, char **new_args, char **env, int i)
{
	char	*ret;
	char	*name;
	char	*s;

	if (!check_str(*args, env, 0, 1) || already_present(new_args, args[0]))
		return (NULL);
	if (check_in_env_char(env, args[0]))
		ret = ft_strdup(check_in_env_char(env, args[0]));
	else
		ret = var_name(args[0]);
	name = var_name(args[0]);
	while (args[i])
	{
		if (!check_str(args[i], env, 0, 0) && !args[i + 1])
			break ;
		else if (!check_str(args[i], env, 0, 0))
			i++;
		s = var_name(args[i]);
		if (args[i] && ft_strncmp(s, name, biggest_str(name, s)) == 0)
			create_str(&args[i], &ret);
		free(s);
		i++;
	}
	return (free(name), ret);
}
