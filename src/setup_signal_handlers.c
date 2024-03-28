/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal_handlers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:07:57 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/26 11:23:22 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t sigint_received;

static void sigint_handler()
{
    sigint_received = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
    //write(STDOUT_FILENO, "\n\001\033[1;34m\002minishell\001\033[0m\002$ ", 28);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);//TODO handle error
    }
}
