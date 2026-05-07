/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:01:17 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/02 21:55:22 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ft_printf_error/libftprintf_error.h"

typedef struct s_info
{
	int		line;
}				t_info;

//error.c
void	closes(int *fd, int file);
void	write_error(char *erro);
void	invalid_cmd(char **cmds, char *cmd);
void	no_perms_cmd(char **cmds, char *cmd);
void	string_null(char **cmds);

//ft_env_line.c
int		ft_env_line(char **big_env, char *str);

//utils.c
char	*path_to_create(char *cmd, char **envp, char **cmds);
void	exec_comand(char *cmd, char **envp);

#endif