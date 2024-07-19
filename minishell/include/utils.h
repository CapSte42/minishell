/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:16:14 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:41:57 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//PROCESS
pid_t	ft_getpid(void);

//ENVIRONMENT
void	set_shlvl(char ***env);
char	**ft_duplicate_env(pid_t *pid);

//VARIOUS
char	*handle_empty_quotes(char *input);

//MAIN_FLOW
void	main_loop(char **rl, t_token **token, char ***env_copy);
//HERE_DOC
void	ft_priority_heredoc(t_redir *files);

#endif
