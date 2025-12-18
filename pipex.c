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

char *find_envpathforcmd(char *cmd, char **envp)
{
	int		i;
	char	*temp_path;
	char	**path;

	path = NULL;
	i = -1;
	while(envp[++i] && !path)
	{
		if(ft_strncmp(envp[i],"PATH=",5) == 0)
			path = ft_split(envp[i] + 5, ':');
	}
	i = -1;
	while(path[++i])
	{
		temp_path = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if(access(temp_path, X_OK) == 0)
			return temp_path;
	}
	return NULL;
}

char **format_argv(char *av, char **envp)
{
	char **av_formated;
	char *temp;

	if (!av)
		return NULL;
	av_formated = ft_split(av, ' ');
	if(av_formated[0] == NULL || av_formated[0][0] == '\0')
		return NULL;

	temp = find_envpathforcmd(av_formated[0], envp);
	if(temp == NULL)
		return NULL;
	free(av_formated[0]);
	av_formated[0] = temp;
	return(av_formated);
}

int docommand(char **cmd, int infile, int outfile, int *pipefd, char **envp)
{
	int pid;
	char **args;

	pid = fork();
	args = format_argv(cmd[2], envp);
	if(pid == 0)//child
	{
		//close(pipefd[0]);

		//dup2(infile , STDIN_FILENO);
		//dup2(pipefd[1] , STDOUT_FILENO);

		//close(pipefd[1]);


		execve(args[0], args, envp);
	}
	execve(args[0], args, envp);
	return (pid);
}

int main(int ac, char **av, char **envp)
{
	int pipefd[2];
	int infile;
	int outfile;
	int pid_1;

	if(ac != 5)
		return(0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	(void)outfile;
	if(infile == -1 || outfile == -1)
			return (1);
	if(pipe(pipefd) == -1)
		return (1);
	pid_1 = docommand(av, infile, outfile, pipefd, envp);
	close(pipefd[0]);
	close(pipefd[1]);

	waitpid(pid_1, NULL, 0);
	//waitpid(pid_2, NULL, 0);
	return (0);
}
