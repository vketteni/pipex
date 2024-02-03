/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:20:39 by vketteni          #+#    #+#             */
/*   Updated: 2024/02/03 18:22:06 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	execute_command(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	path = get_path(cmd_split[0], envp);
	if (execve(path, cmd_split, envp) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_string_arr(cmd_split);
		exit(-1);
	}
}

void	parent_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[4], F_OK | W_OK) == 0)
	{
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		execute_command(argv[3], envp);
	}
}

void	child_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[1], F_OK | R_OK) == 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(-1);
		dup2(fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		execute_command(argv[2], envp);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(-1);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(pipe_fd, argv, envp);
	else
		parent_process(pipe_fd, argv, envp);
	return (0);
}
