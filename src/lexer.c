/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor42 <smontuor42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:57:32 by smontuor          #+#    #+#             */
/*   Updated: 2024/03/28 04:59:08 by smontuor42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_type_2(char *token, char **line)
{
	if (ft_isredin(token) == RED_IN)
		*line = ft_freejoin_char(*line, RED_IN);
	else if (ft_isredout(token) == RED_OUT)
		*line = ft_freejoin_char(*line, RED_OUT);
	else if (ft_isappend(token) == APPEND)
		*line = ft_freejoin_char(*line, APPEND);
	else if (ft_isheredoc(token) == HERE_DOC)
		*line = ft_freejoin_char(*line, HERE_DOC);
	else if (ft_isand(token) == AND)
		*line = ft_freejoin_char(*line, AND);
	else if (ft_isor(token) == OR)
		*line = ft_freejoin_char(*line, OR);
	else if (ft_issemicolon(token) == SEMICOLON)
		*line = ft_freejoin_char(*line, SEMICOLON);
	else if (ft_isparenthesis_o(token) == PARENTHESIS_O)
		*line = ft_freejoin_char(*line, PARENTHESIS_O);
	else if (ft_isparenthesis_c(token) == PARENTHESIS_C)
		*line = ft_freejoin_char(*line, PARENTHESIS_C);
	else if (ft_isword(token) == WORD)
		*line = ft_freejoin_char(*line, WORD);
	else
		*line = ft_freejoin_char(*line, NONE);
}

static void	search_type_1(char *token, char **line)
{
	if (ft_iscmd(token) == CMD)
		*line = ft_freejoin_char(*line, CMD);
	else if (ft_ispipe(token) == PIPE)
		*line = ft_freejoin_char(*line, PIPE);
	else if (ft_issquote(token) == S_QUOTE)
		*line = ft_freejoin_char(*line, S_QUOTE);
	else if (ft_isdquote(token) == D_QUOTE)
		*line = ft_freejoin_char(*line, D_QUOTE);
	else if (ft_isdir(token) == DIRECTORY)
		*line = ft_freejoin_char(*line, DIRECTORY);
	else if (ft_isfile(token) == MY_FILE)
		*line = ft_freejoin_char(*line, MY_FILE);
	else if (ft_isspace(token[0]))
		*line = ft_freejoin_char(*line, SSPACE);
	else if (ft_isarg(token) == FLAG)
		*line = ft_freejoin_char(*line, FLAG);
	else
		search_type_2(token, line);
}

static int	ft_isprint_exceptions(int c, int flag)
{
	if ((!flag) && ' ' <= c && c <= '~'
		&& c != '\"'
		&& c != '\''
		&& c != '|'
		&& c != '<'
		&& c != '>'
		&& c != '&'
		&& c != ';'
		&& c != '('
		&& c != ')')
		return (1);
	if ((flag) && ' ' <= c && c <= '~'
		&& c != '|'
		&& c != '<'
		&& c != '>'
		&& c != '&')
		return (1);

	return (0);
}



void	lexer(char *input, char **line) //TODO: split function
{
	int		input_index;
	int		input_len;
	int		char_start;
	int		char_end;
	char	*token;
	int		flag = 0;
	t_list	

	input_index = 0;
	input_len = ft_strlen(input);
	while (input_index < input_len)
	{
		char_start = input_index;
		while (ft_isprint_exceptions(input[input_index], 0) && !ft_isspace(input[input_index]) && input_index < input_len)
			input_index++;
		while (!ft_isprint_exceptions(input[input_index], 1) && !ft_isspace(input[input_index]) && input_index < input_len && flag < 2)
		{
			input_index++;
			flag++;
		}
		flag = 0;
		if (char_start == input_index)
			input_index++;
		char_end = input_index;
		token = ft_substr(input, char_start, char_end - char_start);
		search_type_1(token, line);
		free(token);
	}
	printf("%s\n", *line);//TODO: remove
}