/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:51:59 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/19 02:46:25 by sarayapa         ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
	int pipefd[2];
	int pipe_err[2];
	int infile;
	int outfile;
	int pid_1;
	int pid_2;
	char **args1;
	char **args2;

	if(ac != 5)
		return(0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC , 0644 );
	if(infile == -1 || outfile == -1)
		return (1);
	if(pipe(pipefd) == -1 || pipe(pipe_err) == -1)
		return (1);

	pid_1 = fork();
	if(pid_1 == 0)//child
	{
		close(pipefd[0]);
		close(pipe_err[0]);

		dup2(infile , STDIN_FILENO);
		dup2(pipefd[1] , STDOUT_FILENO); //pipe[1] <- input

		close(pipefd[1]);

		args1 = format_argv(av[2], envp);
		if (!args1 || !args1[0])
		{
			write(pipe_err[1], "1", 1);
			exit(1);
		}
		execve(args1[0], args1, envp);
		write(pipe_err[1], "1", 1);
		exit(1);
	}
	pid_2 = fork();
	if(pid_2 == 0)//child2
	{
		close(pipefd[1]);
		close(pipe_err[0]);

		dup2(pipefd[0] , STDIN_FILENO); //pipe[0] -> output
		dup2(outfile , STDOUT_FILENO);

		close(pipefd[0]);

		args2 = format_argv(av[3], envp);
		if (!args2 || !args2[0])
		{
			write(pipe_err[1], "1", 1);
			exit(1);
		}
		execve(args2[0], args2, envp);
		write(pipe_err[1], "1", 1);
		exit(1);

	}

	close(pipefd[0]);
	close(pipefd[1]);

	close(pipe_err[1]);

	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);

	char c;
	int n = read(pipe_err[0], &c, 1);
	write(STDIN_FILENO, &n, 1);
	close(pipe_err[0]);

	if(n > 0)
		exit(1);
	return 0;
}


/*
./pipex {file1} {cmd1} {cmd2} {file2}

< pipex.c ls | wc -w > txt
☺  make debug && ./pipex input "echo hello" cat output                                                                                                                                                                                                       main ✗
> make debug &&  valgrind --leak-check=full ./pipex input "cat" "wc -l" output && code output                                                               main [ff731d0] modified untracked
*/