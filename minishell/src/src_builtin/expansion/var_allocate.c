/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_allocate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:36:46 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update(t_count *count)
{
	count->i += 1;
	count->count += 1;
}

static void	handle_dollar(char *str, t_count *count, char **env)
{
	int	tmp;
	int	tmp1;

	if (ft_strncmp(&str[count->i], "$$", 2) == 0)
	{
		tmp = var_value_len(env, &str[count->i]);
		tmp1 = 2;
	}
	else if (ft_strncmp(&str[count->i], "$?", 2) == 0)
	{
		tmp = var_value_len(env, &str[count->i]);
		tmp1 = 2;
	}
	else
	{
		tmp = var_value_len(env, &str[count->i + 1]);
		tmp1 = var_name_len(&str[count->i + 1], env) + 1;
	}
	if (tmp == 0)
		tmp = 1;
	count->count += tmp;
	count->i += tmp1;
}

static void	handle_single(char *str, t_count *count)
{
	update(count);
	while (str[count->i] != 39)
		update(count);
	if (str[count->i])
		update(count);
}

static void	handle_double(char *str, t_count *count, char **env)
{
	update(count);
	while (str[count->i] != 34)
	{
		if (str[count->i] == '$')
			handle_dollar(str, count, env);
		else
			update(count);
	}
	if (str[count->i])
		update(count);
}

/* Cerco variabili $var da espandere.
   Se ne trovo ritorno la nuova stringa espansa,
   altrimenti ritorno la stringa originale */
int	var_allocate(char *str, char **env)
{
	t_count	count;

	count = (t_count){0, 0};
	while (str[count.i])
	{
		if (str[count.i] == 39 && ft_strchr(&str[count.i + 1], 39))
			handle_single(str, &count);
		else if (str[count.i] == 34 && ft_strchr(&str[count.i + 1], 34))
			handle_double(str, &count, env);
		else if (str[count.i] == '$')
			handle_dollar(str, &count, env);
		else
			update(&count);
	}
	return (count.count + 1);
}
