#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include "./libft.h"

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

int	main(int argc, char **av, char **envp)
{

	printf("here");
	char **args1 = format_argv(av[1], envp);
	if (args1 == NULL)
    {
        //fprintf(stderr, "%s: command not found\n", av[1]);
		printf("exit");
        exit(127);   // มาตรฐาน POSIX
    }
	printf("execute");
	execve(args1[0], args1, envp);
	return(0);
}