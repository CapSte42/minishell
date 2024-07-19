/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:39:34 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/13 14:41:35 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

/* cd */
int			find_in_env(char **env, char *to_find);
int			ft_cd(t_data **data);
char		*my_getcwd(void);
char		*print_and_free(char **to_free, char *print);
int			print_and_return(char **to_free, char *print, char *dir);

/* echo */
int			ft_echo(t_data **data, int i);

/* env */
char		**init_env(char **env);
int			has_value(char *str);
size_t		matrix_len(char **env);
int			ft_env(t_data **data);

/* expansion */
int			check_quotes(char *str, int i);
void		expand_and_copy(t_expand *e, int flag);
void		fill_str(char *str, char *to_fill);
int			quotes_count(char *str, int start, int i);
char		*quotes_expansion(char *str, int i, int j);
int			var_allocate(char *str, char **env);
int			var_count(char *str, t_data **data);
int			var_name_len(char *str, char **env);
char		*var_expansion(char **env, char *str, int i, int j);
int			var_value_len(char **env, char *to_check);

/* export */
int			check_double(char **args, int index, char *to_check);
int			check_in_env(char **env, char *to_check);
char		*check_in_env_char(char **env, char *to_check);
int			check_str(char *str, char **env, int i, int flag);
char		**copy_env(char **env);
char		*find_value(char **args, char **new_args, char **env, int i);
int			ft_export(t_data **d, int i, int j, int exit_val);
int			ft_strcmp_env(char *s1, char *s2);
void		ft_print_export_menu(char **env, int i);
char		*get_var_value(char **env, char *to_check);
int			value_sign(char *str);
char		*var_name(char *str);
void		free_and_copy(t_data **d, char **new_args, int *i, int *j);

/* exit */
long long	ft_atoll(const char *nptr);
int			ft_exit(t_data **data);
int			is_digit(char *str);
int			is_digit_exit(char *str);
void		set_exit_value(char **env, int exit);

/* pwd */
int			ft_pwd(t_data **data);

/* unset */
int			biggest_str(char *s1, char *s2);
int			ft_unset(t_data **data);
int			biggest_str(char *s1, char *s2);

/* utils */
void		ft_destroy_fd(int *fd);
int			ft_built_ins(t_node *nodo);

/* wildcard */
char		**ft_check_wildcard(t_data *data);
int			ft_refactor_wild_arg(
				t_data *data, char **args, int index[3], t_wildcard *w);
int			check_wildcard(const char *entry_name, const char *pattern);
char		*get_dir_path(char *arg);
void		ft_init_index(int index[3]);
char		*find_path(char *cmd);
size_t		ft_args_len(char **args);
size_t		args_num(t_data *data);
size_t		ft_files_in_dir(DIR *dir);
int			is_wildcard_unquoted(const char *str);
#endif
