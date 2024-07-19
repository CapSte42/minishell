/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fix_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:13:43 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/03 16:22:51 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_easy_fix(t_data *data, size_t i, size_t args_len)
{
	size_t	n_words;
	size_t	new_size;
	size_t	j;
	char	**new_args;
	char	**buf;

	n_words = count_words(data->args[i], ' ');
	new_size = n_words + args_len - 1;
	j = 0;
	new_args = ft_calloc(new_size + 1, sizeof(char *));
	buf = ft_split(data->args[i], ' ');
	while (j < new_size)
	{
		if (j < i)
			new_args[j] = ft_strdup(data->args[j]);
		else if (j < (n_words + i))
			new_args[j] = ft_strdup(buf[j - i]);
		else
			new_args[j] = ft_strdup(data->args[j - n_words + 1]);
		j++;
	}
	ft_free_matrix(data->args);
	ft_free_matrix(buf);
	data->args = new_args;
}

void	ft_fix_args(t_data *data, int i)
{
	if (ft_strncmp(data->args[0], "export\0", 7) == 0)
		return ;
	if (data->args[i] == NULL)
		return ;
	ft_easy_fix(data, i, ft_args_len(data->args));
}
