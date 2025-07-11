/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:30:34 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 11:51:45 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main_exit(t_data *data)
{
	if (!data)
		return (EXIT_FAILURE);
	if (data->outfile_fd == -1)
		return (EXIT_FAILURE);
	if (data->exec_error == true)
		return (127);
	if (WIFEXITED(data->wtpd))
		return (WEXITSTATUS(data->wtpd));
	if (data->infile_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_cmd_argv(char **cmd_argv)
{
	char	**tmp;

	if (!cmd_argv)
		return ;
	tmp = cmd_argv;
	while (*cmd_argv)
	{
		free(*cmd_argv);
		cmd_argv++;
	}
	free(tmp);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		free_cmd_argv(cmd->args);
		if (cmd->cmd)
			free(cmd->cmd);
		tmp = cmd;
		cmd = cmd->next;
		if (tmp)
			free(tmp);
	}
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->res_path)
	{
		i = 0;
		while (data->res_path[i])
			free(data->res_path[i++]);
		free(data->res_path);
	}
	if (data->cmd)
		free_cmd(data->cmd);
	free(data);
}
