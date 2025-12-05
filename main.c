#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include "./libft.h"

char *find_envpathforcmd(char *cmd, char **envp)
{
	int i;
	char *temp_path;
	char **path;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=",5) == 0)
			path = ft_split(envp[i] + 5, ':');
		i++;
	}
	i = 0;
	while(path[i])
	{
		temp_path = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		printf("%s\n", temp_path);
		if(access(temp_path, X_OK) == 0)
			return temp_path;
		i++;
	}
	return NULL;
}
int	main(int argc, char **argv, char **envp)
{
	//char *envpath;
	//char **path;


	//char *temp[10];
	//for (int i = 0; path[i] ; i++)
	//{
	//	temp[i] = ft_strjoin(path[i], "/reboot");
	//	printf("%s\n",temp[i]);
	//	if((access(temp[i], X_OK) == 0))
	//	{
	//		printf("X_OK : %s\n",temp[i]);
	//		return(0);
	//	}
	//}
	//printf("%s\n\n", find_envpathforcmd("reboot", envp));
	//printf("%s\n\n", find_envpathforcmd("ls", envp));
	printf("here");
	printf("%d",execvp(argv[0] , argv));
	//for(int i = 0; envp[i]; i++)
	//{
	//	printf("%s\n",envp[i]);
	//}
	return(0);
}