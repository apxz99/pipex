/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:34:59 by sarayapa          #+#    #+#             */
/*   Updated: 2026/01/23 14:54:11 by sarayapa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	error_exit(char **exit_name, int errno, int code)
{
	if (errno == PATH)
		write(2, "pipex: no such file or directory: ", 34);
	else if (errno == PERMISSION)
		write(2, "pipex: permision denied: ", 25);
	else if (errno == COMMAND)
		write(2, "pipex: command not found: ",28);
	if (*exit_name)
		ft_putstr_fd(*exit_name, 2);
	free(*exit_name);
	ft_putstr_fd("\n", 2);
	exit(code);
}

void	free_error(char **tab, int errno, int code)
{
	char *cmd;

	cmd = ft_strdup(tab[0]);
	ft_free_tab(tab);
	error_exit(&cmd, errno, code);
}

void	handle_child_processes(t_pipex *px)
{
    int	status;
    int	waited_pid;

	waited_pid = waitpid(-1, &status, 0);
    while (waited_pid > 0)
    {
		if (waited_pid == px->pid[1] && WIFEXITED(status))
			px->status_child2 = WEXITSTATUS(status);
		waited_pid = waitpid(-1, &status, 0);
    }
}
