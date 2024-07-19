/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:05:44 by smontuor          #+#    #+#             */
/*   Updated: 2024/05/13 18:30:27 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

void		lexer(char *input, t_token **token);
int			ft_is_exception(int c);
int			ft_is_double_exception(int c, int prev_c);
t_type		ft_iscmd(char *input);
t_type		ft_isdir(char *input);
t_type		ft_isfile(char *input);
t_type		ft_isword(char *input);
t_type		ft_isand(char *token);
t_type		ft_isappend(char *token);
t_type		ft_isheredoc(char *token);
t_type		ft_isor(char *token);
t_type		ft_get_token_type(char *token);

#endif
