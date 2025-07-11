/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:16:02 by algultse          #+#    #+#             */
/*   Updated: 2024/04/05 13:25:56 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*new_cmd(char *cmd, char **args)
{
	t_cmd	*new_cmd;

	if (!cmd)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = cmd;
	new_cmd->args = args;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

bool	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*tmp;

	if (!cmds || !new)
		return (false);
	if (!*cmds)
	{
		new->prev = NULL;
		new->next = NULL;
		*cmds = new;
		return (true);
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	tmp->next->next = NULL;
	return (true);
}

char	*find_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*res_cmd;

	if (!paths || !cmd)
		return (NULL);
	if (access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			return (NULL);
		res_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!res_cmd)
			return (NULL);
		if (access(res_cmd, 0) == 0)
			return (res_cmd);
		free(res_cmd);
		paths++;
	}
	return (ft_strdup(cmd));
}

char	**split_cmd_argv(char *argv, char **res_path, char **data_cmd)
{
	char	*cmd;
	char	**cmd_args;
	char	*tmp;

	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		return (NULL);
	if (!cmd_args[0])
	{
		free(cmd_args);
		if (data_cmd)
			*data_cmd = ft_strdup(argv);
		return (NULL);
	}
	if (data_cmd)
		*data_cmd = find_cmd_path(res_path, cmd_args[0]);
	cmd = ft_strrchr(cmd_args[0], '/');
	if (!cmd)
		return (cmd_args);
	tmp = ft_strdup(cmd + 1);
	free(cmd_args[0]);
	cmd_args[0] = tmp;
	return (cmd_args);
}
