/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:31:31 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/05 11:25:03 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(char **paths, char *cmd)
{
	int		line;
	char	*aux_path;
	char	*path;

	line = 0;
	while (paths[line])
	{
		aux_path = ft_strjoin(paths[line], "/");
		path = ft_strjoin(aux_path, cmd);
		free(aux_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_double_pointer(paths);
			return (path);
		}
		free(path);
		line++;
	}
	ft_free_double_pointer(paths);
	return (NULL);
}

char	*path_to_create(char *cmd, char **envp, char **cmds)
{
	char	**paths;
	char	*path;
	int		line;

	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	if (!envp[0])
		invalid_cmd(cmds, cmd);
	line = ft_env_line(envp, "PATH=");
	if (line == -1)
		invalid_cmd(cmds, cmd);
	paths = ft_split(envp[line] + 5, ':');
	path = check_path(paths, cmd);
	return (path);
}

void	exec_comand(char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0] || !cmd[0][0])
		string_null(cmd);
	path = path_to_create(cmd[0], envp, cmd);
	if (!path)
		invalid_cmd(cmd, cmd[0]);
	if (access(path, F_OK) != 0)
		invalid_cmd(cmd, cmd[0]);
	if (access(path, X_OK) != 0)
		no_perms_cmd(cmd, cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		ft_free_double_pointer(cmd);
		write_error(av);
	}
}
