/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicchio <tpicchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:25:37 by tpicchio          #+#    #+#             */
/*   Updated: 2024/05/21 15:32:57 by tpicchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msg_error(char *cmd, char *msg)
{
	ft_printf_fd(2, "minishell: %s: %s\n", cmd, msg);
}

void	ft_interpret_exit_val(int *exit_val)
{
	if (WIFEXITED(*exit_val))
	{
		*exit_val = WEXITSTATUS(*exit_val);
	}
	else if (WIFSIGNALED(*exit_val))
	{
		*exit_val = WTERMSIG(*exit_val) + 128;
	}
	else
	{
		ft_printf_fd(2, "minishell: strange error\n");
		*exit_val = 1;
	}
}

static int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

static int	is_binary_file(const char *path)
{
	unsigned char	buffer[4];
	struct stat		path_stat;
	ssize_t			bytes_read;
	int				fd;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (!S_ISREG(path_stat.st_mode) || !(path_stat.st_mode & S_IXUSR))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes_read < 4)
		return (0);
	if (buffer[0] == 0x7f && buffer[1] == 'E'
		&& buffer[2] == 'L' && buffer[3] == 'F')
		return (1);
	return (0);
}

int	ft_is_executable(char *cmd)
{
	if (ft_strchr(cmd, '/') == NULL)
		return (msg_error(cmd, "command not found"), 127);
	if (is_directory(cmd))
		return (msg_error(cmd, "Is a directory"), 126);
	else if (cmd[ft_strlen(cmd) - 1] == '/')
		return (msg_error(cmd, "Not a directory"), 126);
	if (access(cmd, F_OK) == -1)
		return (msg_error(cmd, "No such file or directory"), 127);
	if (access(cmd, X_OK) == -1)
		return (msg_error(cmd, "Permission denied"), 126);
	if (!is_binary_file(cmd))
		return (msg_error(cmd, "Cannot execute non binary file"), 126);
	return (1);
}
