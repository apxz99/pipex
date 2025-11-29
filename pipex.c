/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:51:59 by sarayapa          #+#    #+#             */
/*   Updated: 2025/11/28 20:33:31 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

char **format_argv(char *av)
{
	char **av_formated;
	char *temp;

	temp = ft_strjoin("/usr/bin/", av);
	av_formated = ft_split(temp, ' ');
	free(temp);

	return(av_formated);
}

int main(int ac, char **av)
{
	int pipefd[2];
	int infile;
	int outfile;
	int pid;
	char **args;
	extern char **environ;

	if(ac != 5)
		return(0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[4], O_WRONLY | O_CREAT , 0777);

	pipe(pipefd);
	pid = fork();
	if(pid == 0)
	{
		//dup2(STDOUT_FILENO, infile);
		dup2(outfile , STDOUT_FILENO);
		printf("helo");
		args = format_argv(av[2]);
		execve(args[0], args, environ);
	}
	dup2(infile , STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);

	(void)infile;
	(void)outfile;
}


/*
./pipex {file1} {cmd1} {cmd2} {file2}

< pipex.c ls | wc -w > txt
☺  make debug && ./pipex input "echo hello" cat output                                                                                                                                                                                                       main ✗

*/