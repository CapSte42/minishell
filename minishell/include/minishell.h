/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:54:52 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:37:17 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <sys/types.h>
# include <termios.h>
# include <ncurses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft.h"
# include "struct.h"
# include "token.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "get_rl.h"
# include "built_in.h"
# include "utils.h"

# define HOME	-3
# define STATUS	-2
# define PID	-1

# define NVI	" not a valid identifer\n"

# ifndef DEBUG
#  define DEBUG 0
# endif

void		init_data(t_data **proc);
void		my_add_history(char *line);
void		load_history(void);

void		setup_signal_handlers(void);
char		*handle_empty_quotes(char *input);

#endif
