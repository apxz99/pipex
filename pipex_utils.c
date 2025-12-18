/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 02:23:16 by sarayapa          #+#    #+#             */
/*   Updated: 2025/12/19 02:23:47 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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