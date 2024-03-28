/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 02:09:29 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(".history", O_RDONLY);
	if (fd == -1)
		return ;
	line = ft_get_next_line_no_nl(fd);
	while (line != NULL)
	{
		if (ft_strlen(line) > 0 && ft_isspace_all(line) == 0)
			add_history(line);
		free(line);
		line = ft_get_next_line_no_nl(fd);
	}
	ft_get_next_line_no_nl(-42);
	close(fd);
}
