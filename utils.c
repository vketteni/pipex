/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:20:56 by vketteni          #+#    #+#             */
/*   Updated: 2024/02/04 00:38:28 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_all_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**env_all_path;
	char	**cmd_split;
	char	*env_path;
	char	*executable_path;
	int		i;

	env_all_path = ft_split(get_env_all_path(envp), ':');
	if (env_all_path == NULL)
		return (NULL);
	i = -1;
	cmd_split = ft_split(cmd, ' ');
	while (env_all_path[++i])
	{
		env_path = ft_strjoin(env_all_path[i], "/");
		executable_path = ft_strjoin(env_path, cmd_split[0]);
		free(env_path);
		if (access(executable_path, F_OK | X_OK) == 0)
		{
			free_string_arr(cmd_split);
			return (executable_path);
		}
	}
	free(executable_path);
	free_string_arr(cmd_split);
	return (NULL);
}

void	free_string_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	msg_error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}
