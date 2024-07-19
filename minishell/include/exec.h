/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:04:25 by tpicchio          #+#    #+#             */
/*   Updated: 2024/06/13 14:41:43 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define DEFAULT	0

# include "minishell.h"

// tree_utils.c
t_node	*ft_find_tree_head(t_node *tree);
int		ft_tree_size(t_node *tree);
void	ft_free_tree(t_node *tree);
void	ft_free_redir_list(t_redir *files);

// tree_algo.c
t_node	*ft_find_next(t_node *tree, int start, int end);
void	ft_link_tree(t_node *branch, int pos);

// exec_tree.c
int		ft_exec_tree(t_node *nodo);

// execution.c
void	ft_launch_cmd(t_node *nodo);
void	ft_exec_cmd(t_node *nodo, int *fd);
void	close_fd(int *fd);

// redirect.c
int		ft_manage_redirect(t_redir *files, char **env, int *fd);

pid_t	ft_launch_cmd_pipe(t_node *nodo, int flag, int *stdio_cpy);

// exec_utils.c
void	msg_error(char *cmd, char *msg);
void	ft_interpret_exit_val(int *exit_val);
int		ft_is_executable(char *cmd);

// exec_utils2.c
void	ft_restore_std_io(int *stdio_copy);
char	*ft_search_path(char *cmd, char **env);

#endif
