/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:33:28 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir_path(char *arg)
{
	char	*directory;
	char	*last;

	if (arg[ft_strlen(arg) - 1] == '/')
		arg[ft_strlen(arg) - 1] = '\0';
	last = ft_strrchr(arg, '/');
	if (last != NULL)
	{
		last++;
		dbg(DEBUG, "last = %p\targ = %p\n", last, arg);
		directory = ft_calloc((last - arg + 1), sizeof(char));
		if (!directory)
			return (free(arg), ft_strdup("."));
		ft_strlcpy(directory, arg, (last - arg) + 1);
		return (free(arg), directory);
	}
	else
		return (free(arg), ft_strdup("."));
}

static int	elser(const char **entry_ptr, const char **pattern_ptr,
	const char **wildcard_ptr, const char **entry_after_wildcard)
{
	char	quote;

	if (**pattern_ptr == **entry_ptr)
	{
		*entry_ptr = *entry_ptr + 1;
		*pattern_ptr = *pattern_ptr + 1;
	}
	else if (*wildcard_ptr != NULL)
	{
		*pattern_ptr = *wildcard_ptr + 1;
		*entry_ptr = ++(*entry_after_wildcard);
	}
	else if (**entry_ptr == '\"' || **entry_ptr == '\'')
	{
		quote = **entry_ptr;
		while (**entry_ptr != quote)
		{
			if (**(entry_ptr + 1) == '\0')
				return (0);
			*entry_ptr = *entry_ptr + 1;
		}
	}
	else
		return (0);
	return (1);
}

static int	refactor(const char **entry_ptr, const char **pattern_ptr,
	const char **wildcard_ptr, const char **entry_after_wild)
{
	while (**entry_ptr != '\0')
	{
		if (**pattern_ptr == '*')
		{
			*wildcard_ptr = *pattern_ptr;
			*pattern_ptr = *pattern_ptr + 1;
			*entry_after_wild = *entry_ptr;
		}
		else if (!elser(entry_ptr, pattern_ptr, wildcard_ptr, entry_after_wild))
			return (0);
	}
	while (**pattern_ptr == '*')
		*pattern_ptr = *pattern_ptr + 1;
	return (**pattern_ptr == '\0');
}

int	check_wildcard(const char *entry_name, const char *pattern)
{
	const char	*entry_ptr = entry_name;
	const char	*pattern_ptr = pattern;
	const char	*wildcard_ptr = NULL;
	const char	*entry_after_wild = NULL;

	if (entry_name == NULL || pattern == NULL)
		return (0);
	if (ft_strncmp(entry_name, ".\0", 2) == 0
		|| ft_strncmp(entry_name, "..\0", 3) == 0)
		return (0);
	return (refactor(&entry_ptr, &pattern_ptr,
			&wildcard_ptr, &entry_after_wild));
}
