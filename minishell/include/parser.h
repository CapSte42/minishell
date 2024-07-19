/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:49:17 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/03 16:23:19 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parser(char *input, t_token **token);
int		check_balance(const char *str);
t_token	*skip_space_tokens(t_token *token);
int		print_syntax_error(char *extract);
int		check_syntax(t_token *tokens);
void	ft_check_expand(t_data *leaf);
void	handle_logic_operator(t_token *prev, t_token *current,
			t_token *next, int *flag);
void	handle_redirect_operator(t_token *prev, t_token *current,
			t_token *next, int *flag);
void	handle_parenthesis_open_operator(t_token *prev, t_token *current,
			t_token *next, int *flag);
void	handle_parenthesis_close_operator(t_token *prev, t_token *current,
			t_token *next, int *flag);
void	handle_word_operator(t_token *prev, t_token *current,
			t_token *next, int *flag);
void	quote_handling(t_token **token_list);
void	merge_near_word(t_token **token);
int		check_grammatical_rules(t_token *token);
void	ft_fix_args(t_data *data, int i);

#endif
