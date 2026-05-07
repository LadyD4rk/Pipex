/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jobraga- <jobraga-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:02:36 by jobraga-          #+#    #+#             */
/*   Updated: 2025/09/02 20:42:33 by jobraga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_one(char **av, char *envp[], int fd[])
{
	int		file1;

	file1 = open(av[1], O_RDONLY);
	if (file1 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		write_error(av[1]);
	}
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	closes(fd, file1);
	exec_comand(av[2], envp);
	exit(1);
}

void	child_process_two(char **av, char *envp[], int fd[])
{
	int		file2;

	file2 = open (av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		write_error(av[4]);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	closes(fd, file2);
	exec_comand(av[3], envp);
	exit(1);
}

int	ft_wait(pid_t *pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(pid[1], &status, 0);
	if (WIFEXITED (status))
		exit_code = WEXITSTATUS(status);
	waitpid(pid[0], NULL, 0);
	return (exit_code);
}

int	main(int ac, char **av, char *envp[])
{
	int		fd[2];
	pid_t	pid[2];
	int		exit_sta;

	exit_sta = 1;
	if (ac == 5)
	{
		if (pipe(fd) != 0)
			write_error("pipe_error");
		pid[0] = fork();
		if (pid[0] == 0)
			child_process_one(av, envp, fd);
		else
		{
			pid[1] = fork();
			if (pid[1] == 0)
				child_process_two(av, envp, fd);
		}
		if (close(fd[0]) < 0 || close(fd[1]) < 0)
			write_error("closing error");
		exit_sta = ft_wait(pid);
	}
	else
		write(2, "ERROR: Invalid number of arguments.\n", 37);
	return (exit_sta);
}
