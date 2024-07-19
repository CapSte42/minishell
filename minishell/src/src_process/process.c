/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:09:11 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/16 21:09:51 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(1);
	}
	else if (pid == 0)
	{
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	return (pid);
}
