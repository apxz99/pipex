/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:29:15 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/12 16:29:15 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include <error.h>

void	ft_free(char **strs);

char *find_envpathforcmd(char *cmd, char **envp)
{
	int		i;
	char	*full_path;
	char	**path;
	char	*tmp;

	path = NULL;
	i = -1;
	while(envp[++i] && !path)
	{
		if(ft_strncmp(envp[i],"PATH=",5) == 0)
			path = ft_split(envp[i] + 5, ':');
	}
	if(!path)
		return(NULL);
	i = -1;
	while(path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if(access(full_path, X_OK) == 0)
		{
			ft_free(path);
			return full_path;
		}
		free(full_path);
	}
	ft_free(path);
	return NULL;
}

char **format_argv(char *av, char **envp)
{
	char **av_formated;
	char *temp;

	if (!av)
		return NULL;
	av_formated = ft_split(av, ' ');
	if(!av_formated || av_formated[0] == NULL || av_formated[0][0] == '\0')
	{
		ft_free(av_formated);
		return NULL;
	}
	temp = find_envpathforcmd(av_formated[0], envp);
	if(temp == NULL)
	{
		ft_free(av_formated);
		return NULL;
	}
	free(av_formated[0]);
	av_formated[0] = temp;
	return(av_formated);
}

void do_command_1(t_pipex *px)
{
	px->pid[0] = fork();
	if(px->pid[0] == 0)//child
	{
		close(px->pipefd[0]);
		dup2(px->infile , STDIN_FILENO);
		dup2(px->pipefd[1] , STDOUT_FILENO);
		close(px->pipefd[1]);
		close(px->infile);
		close(px->outfile);
		execve(px->cmd1[0], px->cmd1, px->envp);
		ft_free(px->cmd1);
		exit(127);
	}
}

void do_command_2(t_pipex *px)
{
	px->pid[1] = fork();
	if(px->pid[1] == 0)//child
	{
		close(px->pipefd[1]);
		dup2(px->pipefd[0] , STDIN_FILENO);
		dup2(px->outfile , STDOUT_FILENO);
		close(px->pipefd[0]);
		close(px->infile);
		close(px->outfile);
		execve(px->cmd2[0], px->cmd2, px->envp);
		ft_free(px->cmd2);
		exit(127);
	}
}

void	init_pipex(int ac, char **av, char **envp, t_pipex *px)
{
	px->envp = envp;
	if(ac != 5 || !av[1] || !av[4])
		exit(0);
	px->infile = open(av[1], O_RDONLY);
	px->outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC ,0644);
	if(px->infile == -1 || px->outfile == -1)
		exit(1);
	if(pipe(px->pipefd) == -1)
		exit(1);
	px->cmd1 = format_argv(av[2], px->envp);
	if(!px->cmd1)
	{
		close(px->infile);
		close(px->outfile);
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		exit(127);
	}
	px->cmd2 = format_argv(av[3], px->envp);
	if(!px->cmd2)
	{
		close(px->infile);
		close(px->outfile);
		close(px->pipefd[0]);
		close(px->pipefd[1]);
		exit(127);
	}
}

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int main(int ac, char **av, char **envp)
{
	t_pipex	px;

	init_pipex(ac, av, envp, &px);

	do_command_1(&px);
	do_command_2(&px);

	close(px.pipefd[0]);
	close(px.pipefd[1]);
	close(px.infile);
	close(px.outfile);

	waitpid(px.pid[0], NULL, 0);
	waitpid(px.pid[1], NULL, 0);
	ft_free(px.cmd1);
	ft_free(px.cmd2);
	return (0);
}
//# 2: "infiles/basic.txt" "ls -la" "cat -e" "outfiles/outfile"                             [KO]    [OK]    [OK]    [OK]