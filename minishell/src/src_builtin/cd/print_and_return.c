/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:24:11 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_and_free(char **to_free, char *print)
{
	ft_printf_fd(2, "%s\n", print);
	free(*to_free);
	return (NULL);
}

int	print_and_return(char **to_free, char *print, char *dir)
{
	if (dir != NULL)
		ft_printf_fd(2, "minishell: cd: %s: %s\n", dir, print);
	else
		ft_printf_fd(2, "minishell: cd: %s\n", print);
	free(*to_free);
	return (1);
}
