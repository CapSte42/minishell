/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:51:43 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	args_num(t_data *data)
{
	int			indexes[3];
	t_wildcard	w;

	ft_init_index(indexes);
	return (ft_refactor_wild_arg(data, NULL, indexes, &w) + 1);
}

size_t	ft_files_in_dir(DIR *dir)
{
	size_t	len;

	len = 0;
	while (readdir(dir) != NULL)
		len++;
	return (len);
}

size_t	ft_args_len(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_wildcard_unquoted(const char *str)
{
	int	single_quote;
	int	double_quote;
	int	i;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			single_quote = !single_quote;
		else if (str[i] == '\"')
			double_quote = !double_quote;
		else if (str[i] == '*' && !single_quote && !double_quote)
			return (1);
		i++;
	}
	return (0);
}
