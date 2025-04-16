/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:44:25 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/16 06:18:05 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*find(char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!ft_strncmp(sub, "PATH", 4))
			return (free(sub), env[i] + j + 1);
		free(sub);
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path_env;
	char	*path_part;
	char	*exec;

	i = 0;
	path_env = ft_split(find(env), ':');
	if (!path_env)
		return (NULL);
	while (path_env[++i])
	{
		path_part = ft_strjoin(path_env[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (!access(exec, F_OK | X_OK))
			return (ft_free_split(path_env), exec);
		free(exec);
	}
	return (ft_free_split(path_env), cmd);
}
