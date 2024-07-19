/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:28:43 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_str(t_expand *e)
{
	e->tmp = ft_strdup(get_var_value(e->env, &(e->str)[*(e->i) + 1]));
	fill_str(e->tmp, &e->expanded[*e->j]);
	if (e->tmp == NULL)
		*e->j += 0;
	else
		*e->j += ft_strlen(e->tmp);
	free(e->tmp);
	*e->i += var_name_len(&(e->str)[*(e->i) + 1], e->env - 2) + 1;
}

static void	handle_exit_pid(t_expand *e, int index)
{
	e->tmp = ft_strchr(e->env[index], '=') + 1;
	fill_str(e->tmp, &e->expanded[*e->j]);
	*e->j += ft_strlen(e->tmp);
	*e->i += 2;
}

static void	handle_single_dollar(t_expand *e)
{
	e->expanded[*e->j] = '$';
	*e->i += 1;
	*e->j += 1;
}

static void	handle_special_case(t_expand *e, int flag)
{
	if (flag == 0)
	{
		if (e->str[*(e->i) + 1] == 34 || e->str[*(e->i) + 1] == 39)
			*e->i += 1;
		return ;
	}
	else
	{
		if (ft_isalpha(e->str[*(e->i) + 1]) != 0 || e->str[*(e->i) + 1] == '_')
			handle_str(e);
		else
			handle_single_dollar(e);
		return ;
	}
}

/*  Fare caso speciale per $ piu' spazio, single e double */
void	expand_and_copy(t_expand *e, int flag)
{
	if (ft_strncmp(&(e->str[*(e->i)]), "$?", 2) == 0)
		handle_exit_pid(e, STATUS);
	else if (ft_strncmp(&(e->str[*(e->i)]), "$$", 2) == 0)
		handle_exit_pid(e, PID);
	else if (ft_strncmp(&(e->str[*(e->i)]), "$\"", 2) == 0
		|| ft_strncmp(&(e->str[*(e->i)]), "$\'", 2) == 0)
	{
		handle_special_case(e, flag);
		return ;
	}
	else if (ft_strncmp(&(e->str[*(e->i)]), "$", 1) == 0 && (e->str[*(e->i) + 1]
			&& ft_isalpha(e->str[*(e->i) + 1]) == 0))
		handle_single_dollar(e);
	else if (ft_strncmp(&(e->str[*(e->i)]), "$\0", 2) == 0)
		handle_single_dollar(e);
	else
		handle_str(e);
}
