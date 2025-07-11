/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:03:17 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 13:27:15 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		exit_code;

	if (argc != 5)
		exit_pipex("Usage: ./pipex <infile> cmd1 cmd2 <outfile>\n");
	data = init_data(argc, argv, envp);
	child_process(data, envp);
	exit_code = main_exit(data);
	free_data(data);
	return (exit_code);
}

void	exec_childs(t_data *data, int fd[2], char **envp)
{
	t_cmd	*cmds;
	t_fds	fds1;
	t_fds	fds2;

	if (!data || !data->cmd)
		return ;
	cmds = data->cmd;
	fds1 = (t_fds){\
		.in = data->infile_fd, \
		.out = fd[1], \
		.no = fd[0] \
	};
	cmds->pid = exec_child(fds1, data, cmds, envp);
	if (!data->cmd->next)
		return ;
	cmds = cmds->next;
	fds2 = (t_fds){\
		.in = fd[0], \
		.out = data->outfile_fd, \
		.no = fd[1]};
	cmds->pid = exec_child(fds2, data, cmds, envp);
}

void	child_process(t_data *data, char **envp)
{
	int		fd[2];
	t_cmd	*cmds;

	if (pipe(fd) == -1)
		error_free_exit(data, "Error creating pipe");
	exec_childs(data, fd, envp);
	close(fd[0]);
	close(fd[1]);
	cmds = data->cmd;
	while (cmds)
	{
		data->exec_error = false;
		if ((cmds->pid > -1 && waitpid(cmds->pid, &data->wtpd, 0) == -1) \
			|| cmds->pid == -1)
			data->exec_error = true;
		cmds = cmds->next;
	}
	close(data->infile_fd);
	close(data->outfile_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
