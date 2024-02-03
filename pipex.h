/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:20:48 by vketteni          #+#    #+#             */
/*   Updated: 2024/02/03 23:48:12 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "submodules/libft/libft.h"
# include <errno.h>
# include <fcntl.h>  
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	execute_command(char *cmd, char *envp[]);
void	parent_process(int pipe_fd[2], char *argv[], char *envp[]);
void	child_process(int pipe_fd[2], char *argv[], char *envp[]);
char	*get_env_all_path(char *envp[]);
char	*get_path(char *cmd, char *envp[]);
void	free_string_arr(char **arr);
void	msg_error(char *err);

#endif