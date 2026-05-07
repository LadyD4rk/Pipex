/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:47:29 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/02 21:54:58 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	closes(int *fd, int file)
{
	if (close(fd[0]) < 0 || close(fd[1]) < 0)
		write_error("closing error");
	if (close(file) < 0)
		write_error("closing error");
}

void	invalid_cmd(char **cmds, char *cmd)
{
	ft_printf_error("%s", cmd);
	ft_printf_error(": Command not found \n");
	ft_free_double_pointer(cmds);
	exit (127);
}

void	no_perms_cmd(char **cmds, char *cmd)
{
	ft_printf_error("%s", cmd);
	ft_printf_error(": Permission denied \n");
	ft_free_double_pointer(cmds);
	exit (126);
}

void	string_null(char **cmds)
{
	ft_free_double_pointer(cmds);
	exit(0);
}

void	write_error(char *erro)
{
	perror(erro);
	exit(1);
}
