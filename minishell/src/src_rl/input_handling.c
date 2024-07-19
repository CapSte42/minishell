/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontuor <smontuor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:39:22 by smontuor          #+#    #+#             */
/*   Updated: 2024/06/01 15:23:35 by smontuor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_additional_input(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	return (line);
}

char	*join_strings(char *original, const char *to_add, const char *separator)
{
	char	*new_str;

	new_str = ft_freejoin(original, separator);
	return (ft_freejoin(new_str, to_add));
}

void	configure_input(int flag, t_input_config *config)
{
	if (flag == 1)
	{
		config->prompt = "\001\033[5;34m\002open quote> \001\033[0m\002";
		config->error_message
			= "minishell: unexpected EOF while looking for matching quote";
		config->separator = "\n";
	}
	else
	{
		if (flag == 2)
			config->prompt = "\001\033[5;34m\002continue> \001\033[0m\002";
		else
			config->prompt = "\001\033[5;34m\002(...> \001\033[0m\002";
		if (flag == 3)
			config->error_message
				= "minishell: syntax error: unmatched parenthesis";
		else
			config->error_message
				= "minishell: syntax error: unexpected end of file";
		config->separator = " ";
	}
}

char	*handle_input(char *tmp, int flag, int flag2)
{
	t_input_config	config;
	char			*input;

	input = NULL;
	if (tmp == NULL)
		return (NULL);
	if (flag2 == 0)
	{
		configure_input(flag, &config);
		input = read_additional_input(config.prompt);
	}
	else
		configure_input(3, &config);
	if (input == NULL || flag == 4 || flag2 == 1)
	{
		ft_printf_fd(2, "%s\n", config.error_message);
		free(tmp);
		return ("");
	}
	tmp = join_strings(tmp, input, config.separator);
	free(input);
	return (tmp);
}
