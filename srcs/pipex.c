/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:00:14 by sarayapa          #+#    #+#             */
/*   Updated: 2026/01/23 15:06:04 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_envpath_for_cmd(char *cmd, t_pipex *px)
{
	if (!cmd)
		return (NULL);
	px->i = 0;
	while (px->envp[px->i] && ft_strncmp(px->envp[px->i], "PATH=", 5) != 0)
		px->i++;
	if (!px->envp[px->i])
		return (NULL);
	px->path = ft_split(px->envp[px->i] + 5, ':');
	if (!px->path)
		return (NULL);
	px->i = -1;
	while (px->path[++px->i])
	{
		px->tmp = ft_strjoin(px->path[px->i], "/");
		if (!px->tmp)
			return (ft_free_tab(px->path), NULL);
		px->full_path = ft_strjoin(px->tmp, cmd);
		free(px->tmp);
		if (!px->full_path)
    		return (free(px->tmp), ft_free_tab(px->path), NULL);
		if (access(px->full_path, X_OK) == 0)
			return (ft_free_tab(px->path), px->full_path);
		free(px->full_path);
	}
	ft_free_tab(px->path);
	return (NULL);
}

char	**format_argv(char *av, t_pipex *px)
{
	if (!av || av[0] == '\0')
	{
		write(2, "pipex: command not found: ",28);
		return (NULL);
	}
	px->av_formated = ft_split(av, ' ');
	if (!px->av_formated || !px->av_formated[0])
	{
		ft_free_tab(px->av_formated);
		error_exit(NULL, COMMAND, 127);
	}
	if (ft_strrchr(px->av_formated[0], '/'))
	{
		if (access(px->av_formated[0], F_OK) != 0)
			free_error(px->av_formated, PATH, 127);
		if (access(px->av_formated[0], X_OK) != 0)
			free_error(px->av_formated, PERMISSION, 126);
		return (px->av_formated);
	}
	px->temp = find_envpath_for_cmd(px->av_formated[0], px);
	if (!px->temp)
		free_error(px->av_formated, COMMAND, 127);
	free(px->av_formated[0]);
	px->av_formated[0] = px->temp;
	return (px->av_formated);
}

void	do_command_1(t_pipex *px)
{
	px->infile = open(px->av[1], O_RDONLY);
	if (px->infile == -1)
    {
        if (access(px->av[1], F_OK) != 0)
		{
			write(2, "pipex: no such file or directory: ", 34);
			ft_putstr_fd(px->av[4], 2);
			exit(126);
		}
        write(2, "pipex: permision denied: ", 25);
		ft_putstr_fd(px->av[4], 2);
		exit(0);
    }
	if (access(px->av[1], R_OK) != 0)
		error_exit(&px->av[1], PERMISSION, 1);
	px->cmd1 = format_argv(px->av[2], px);
	if (!px->cmd1)
	{
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		close(px->infile);
		exit(127);
	}
	dup2(px->infile, STDIN_FILENO);
	dup2(px->pipefd[1], STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->infile);
	if(execve(px->cmd1[0], px->cmd1, px->envp) == -1)
		ft_free_tab(px->cmd1);
	exit(127);
}

void	do_command_2(t_pipex *px)
{
	px->outfile = open(px->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfile == -1)
	{
		if (access(px->av[4], F_OK) != 0)
		{
			write(2, "pipex: no such file or directory: ", 34);
			ft_putstr_fd(px->av[4], 2);
			exit(127);
		}
		write(2, "pipex: permision denied: ", 25);
		ft_putstr_fd(px->av[4], 2);
		exit(1);
	}
	px->cmd2 = format_argv(px->av[3], px);
	if (!px->cmd2)
	{
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		close(px->outfile);
		exit(127);
	}
	dup2(px->pipefd[0], STDIN_FILENO);
	dup2(px->outfile, STDOUT_FILENO);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->outfile);
	execve(px->cmd2[0], px->cmd2, px->envp);
	exit(127);
}

int	main(int ac, char **av, char **envp)
{
    t_pipex	px;

    px.av = av;
    px.envp = envp;
    if (ac != 5)
        return (ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2), 1);
    if (pipe(px.pipefd) == -1)
        return (0);
    px.pid[0] = fork();
    if (px.pid[0] == 0)
		do_command_1(&px);
    px.pid[1] = fork();
    if (px.pid[1] == 0)
        do_command_2(&px);
    close(px.pipefd[0]);
    close(px.pipefd[1]);
    handle_child_processes(&px);
    return (px.status_child2);
}
