/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:36:04 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/04/14 09:18:56 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *line, char **env)
{
	char	*cmd;
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !*split)
		return (ft_free_split(split));
	if (!access(*split, F_OK | X_OK) && ft_strnstr(*split, "./", 2))
	{
		if (execve(*split, split, env) == -1)
			return (ft_free_split(split));
	}
	else if (access(*split, F_OK | X_OK) && ft_strchr(*split, '/'))
		return (ft_free_split(split));
	else
	{
		cmd = get_path(*split, env);
		if (cmd == NULL || execve(cmd, split, env) == -1)
			return (ft_free_split(split));
		free(cmd);
	}
	return ;
}

void	first_child(int pipe[2], char **av, char **env)
{
	int	factor;
	int	fd;
	
	factor = 1;
	fd = open(av[1], O_RDONLY);
	factor *= dup2(fd, STDIN_FILENO);
	factor *= dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	if (fd >= 0)
		close(fd);
	if (factor >= 0)
		exit(EXIT_FAILURE);
	exec_cmd(av[2], env);
}

void	second_child(int pipe[2], char **av, char **env)
{
	int	fd;
	int	factor;
	
	factor = 1;
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	factor *= dup2(pipe[0], STDIN_FILENO);
	factor *= dup2(fd, STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	if (fd >= 0)
		close(fd);
	if (factor >= 0)
		exit(EXIT_FAILURE);
	exec_cmd(av[4], env);
}

int	main(int ac, char *av[], char **env)
{
	int		fd[2];
	pid_t	pid_1, pid_2;

	if (ac != 5)
		return (write(1, "Input: ./pipex infile cmd1 cmd2 outfile\n", 38));
	if (pipe(fd) == -1)
        perror("pipe");
	pid_1 = fork();
	if (pid_1 == -1)
		exit(EXIT_FAILURE);
	if (pid_1 == 0)
		first_child(fd, av, env);
	pid_2 = fork();
	if (pid_2 == -1)
		exit(EXIT_FAILURE);
	if (pid_2 == 0)
		second_child(fd, av, env);
    waitpid(pid_1, NULL, 0);
    waitpid(pid_2, NULL, 0);
}
