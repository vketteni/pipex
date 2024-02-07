/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:20:39 by vketteni          #+#    #+#             */
/*   Updated: 2024/02/07 21:38:56 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char *envp[])
{
	char	*path;
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	remove_inner_quotes(cmd_split);
	path = get_path(cmd_split[0], envp);
	if (path == NULL)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_string_arr(cmd_split);
		exit(-1);
	}
	if (execve(path, cmd_split, envp) == -1)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_split[0], 2);
		free_string_arr(cmd_split);
		exit(-1);
	}
}

void	parent_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[1], F_OK) == -1)
		msg_error("Infile missing=-");
	if (access(argv[1], R_OK) == -1)
		msg_error("Write access denied.");
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(-1);
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	execute_command(argv[3], envp);
}

void	child_process(int pipe_fd[2], char *argv[], char *envp[])
{
	int	fd;

	if (access(argv[1], F_OK) == -1)
		msg_error("Infile missing");
	if (access(argv[1], R_OK) == -1)
		msg_error("Read access denied.");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(-1);
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	execute_command(argv[2], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (argc != 5)
	{
		ft_putstr_fd("USAGE: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 2);
		exit(-1);
	}
	if (pipe(pipe_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(pipe_fd, argv, envp);
	parent_process(pipe_fd, argv, envp);
	waitpid(pid, &status, 0);
	return (0);
}
