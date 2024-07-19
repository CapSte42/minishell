/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:50:44 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/01 16:21:38 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_type
{
	LEAF			= -1,
	CMD				= 'C',
	WORD			= 'W',
	MY_FILE			= 'F',
	DIRECTORY		= 'D',
	PIPE			= '|',
	S_QUOTE			= '\'',
	D_QUOTE			= '\"',
	RED_IN			= '<',
	RED_OUT			= '>',
	APPEND			= 'A',
	HERE_DOC		= 'H',
	HERE_DOC_E		= 'h',
	NONE			= '?',
	SSPACE			= '-',
	FLAG			= 'f',
	ENV_VAR			= '$',
	SEMICOLON		= ';',
	AND				= 'e',
	OR				= 'o',
	PARENTHESIS_O	= '(',
	PARENTHESIS_C	= ')',
	WILDCARD		= '*',
	NNEWLINE		= '\n',
	END				= '\0',
	TO_JUMP			= 'j'
}					t_type;

typedef struct s_input_config
{
	const char	*prompt;
	const char	*error_message;
	const char	*separator;
}					t_input_config;

typedef struct s_token
{
	t_type			type;
	int				exception;
	int				start;
	int				end;
	char			*extract;
	struct s_token	*next;
}					t_token;

typedef enum e_state
{
	INIT			= 0,
	IN_WORD			= 1,
	IN_SINGLE_QUOTE	= 2,
	IN_DOUBLE_QUOTE	= 3,
	IN_PARENTHESES	= 4,
	IN_LEAF			= 5,
	ERROR			= 6
}					t_state;

typedef struct s_redir
{
	t_type			type;// {RED_IN, RED_OUT, APPEND, HERE_DOC}
	char			*name;
	struct s_redir	*next;
}					t_redir;

typedef struct s_top_node
{
	t_type	type;
	int		depth;
	int		pos;
}				t_top_node;

typedef struct s_data
{
	char			**env;
	t_redir			*files; // null if logical operator
	char			**args;
	int				stdio[2];
}					t_data;

typedef struct s_node
{
	int				depth;
	int				pos;
	t_type			type; // {AND, OR, SEMICOLON, PIPE, LEAF}
	t_data			*data;
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

/* Mini struttura creata per questioni di norminette */
//wow
typedef struct s_expand
{
	char	**env;
	char	*str;
	int		*i;
	int		*j;
	char	*expanded;
	char	*tmp;
}					t_expand;

/* Mini struttura creata per questioni di norminette */
typedef struct s_count
{
	int	i;
	int	count;
}	t_count;

typedef struct s_quote_handler
{
	char	**result;
	int		*index;
	int		*i;
	t_state	*state;
}	t_quote_handler;

typedef struct s_wildcard
{
	char			*dir_path;
	char			*to_append;
	DIR				*dir;
	struct dirent	*entry;
}	t_wildcard;

#endif
