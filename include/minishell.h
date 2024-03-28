/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:54:52 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 04:21:19 by smontuor42       ###   ########.fr       */
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

# include "libft.h"
# include "struct.h"

void		init_proc(t_proc **proc);
void		lexer(char *input, char **line);
void		my_add_history(char *line);
void		load_history(void);

void		setup_signal_handlers(void);

enum type	ft_iscmd(char *token);
enum type	ft_ispipe(char *token);
enum type	ft_isdir(char *token);
enum type	ft_isfile(char *token);
enum type	ft_issquote(char *token);
enum type	ft_isdquote(char *token);
enum type	ft_isarg(char *token);
enum type	ft_isredin(char *token);
enum type	ft_isredout(char *token);
enum type	ft_isappend(char *token);
enum type	ft_isheredoc(char *token);
enum type	ft_isand(char *token);
enum type	ft_isor(char *token);
enum type	ft_issemicolon(char *token);
enum type	ft_isparenthesis_o(char *token);
enum type	ft_isparenthesis_c(char *token);
enum type	ft_isword(char *token);

#endif
