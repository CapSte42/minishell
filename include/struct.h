/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:50:44 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 04:58:49 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum type
{
	CMD				= 'C',
	WORD			= 'W',
	PIPE			= '|',
	S_QUOTE			= '\'',
	D_QUOTE			= '\"',
	MY_FILE			= 'F',
	DIRECTORY		= 'D',
	RED_IN			= '<',
	RED_OUT			= '>',
	APPEND			= 'A',
	HERE_DOC		= 'H',
	NONE			= '?',
	SSPACE			= '-',
	FLAG			= 'f',
	ENV_VAR			= '$',
	SEMICOLON		= ';',
	AND				= '&',
	OR				= 'o',
	PARENTHESIS_O	= '(',
	PARENTHESIS_C	= ')',
	NNEWLINE		= '\n',
	END				= '\0'
};

typedef struct s_token
{
	enum type		type;
	int				start;
	int				end;
}					t_token;

typedef enum {
    STATE_START,
    STATE_IN_WORD,
    STATE_IN_QUOTE,
	STATE_AFTER_QUOTE
} State;

typedef struct s_proc
{
	char			**env;              // Variabili d'ambiente getenv()
	int				fd_in;              // File descriptor per l'input
	int				fd_out;             // File descriptor per l'output
	char			*cmd;               // Il comando da eseguire
	char			**args;        // Argomenti del comando argomenti[0] = cmd
	int				n_args;           // Numero di argomenti in **arguments
	char			*path;          // PATH del comando *NULL* se non trovato
	char			*in_f;       // Percorso del file per la redirezione dell'input
	char			*out_f;      // Percorso del file per la redirezione dell'output
	int				to_append;         // Flag per appendere all'output (>>)
	int				pipe_next;          // Flag/indicatore per pipe con il comando successivo
	int				exit_value;         // Valore di uscita del comando
	enum type		logical;               // && || ;
	struct s_proc	*next;              // Puntatore al prossimo comando
	struct s_proc	*prev;              // Puntatore al comando precedente
}					t_proc;

#endif
