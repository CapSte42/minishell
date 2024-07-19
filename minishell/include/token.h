/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:05:52 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:42:22 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

void		set_token(t_token **token, t_type type, int start, char *extract);
void		token_init(t_token **token);
void		free_tokens(t_token **token);
void		add_token(t_token **token, t_type type, int start, char *extract);
t_type		get_token_type(t_token **token);
int			_start(t_token **token);
char		*get_token_extract(t_token **token);
int			get_token_end(t_token **token);
t_token		*get_next_token(t_token **token);
int			isredirection_operator(t_type type);
int			islogical_operator(t_type type);
int			count_operators(t_token *token);
void		ft_delete_token_file(t_token **tmp);
t_redir		*ft_create_list_files(t_token **tmp);
int			ft_count_args(t_token *tmp);
char		**ft_create_args(t_token *tmp);
t_node		*token_to_array_tree(t_token **token,
				char ***env_copy, int i, int depth);

#endif
