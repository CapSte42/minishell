/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_add_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:08:36 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_add_history(char *line)
{
	int	fd;

	if (ft_strlen(line) > 0 && ft_isspace_all(line) == 0)
	{
		fd = open(".history", O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		close(fd);
		add_history(line);
	}
}
