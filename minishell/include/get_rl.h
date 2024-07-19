/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:37:59 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/01 15:05:26 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_RL_H
# define GET_RL_H

t_state	check_quote_balance(char *rl);
t_state	check_paren_balance(char *rl);
t_type	ft_get_last_token_type(char *rl);
char	*read_additional_input(const char *prompt);
char	*join_strings(char *original, const char *to_add,
			const char *separator);
int		is_continuation_token(t_type type);
char	*handle_input(char *tmp, int flag, int flag2);
int		is_unbalanced(char *tmp, t_state *quote_state,
			t_state *paren_state, t_type *type);
char	*get_rl(void);

#endif
