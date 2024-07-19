/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:57:38 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:39:10 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PWD */
int	ft_pwd(t_data **d)
{
	char		*dir;
	static int	fd[2];

	if ((*d)->files)
		if (ft_manage_redirect((*d)->files, (*d)->env, fd) == -1)
			return (set_exit_value((*d)->env, 1), 1);
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		perror("pwd failed, directory name might be too long\n");
	ft_printf_fd(1, "%s\n", dir);
	free(dir);
	set_exit_value((*d)->env, 0);
	ft_destroy_fd(fd);
	return (0);
}
