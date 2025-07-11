/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:16:13 by algultse          #+#    #+#             */
/*   Updated: 2024/04/05 15:53:33 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	exec_child(t_fds fds, t_data *data, t_cmd *cmd, char **envp)
{
	pid_t	child;

	if (access(cmd->cmd, 0) != 0)
		return (ft_printf("command not found: %s\n", cmd->cmd), -1);
	if (fds.in == -1 || fds.out == -1)
		return (-1);
	child = fork();
	if (child == 0)
	{
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		if (fds.no >= 0)
			close(fds.no);
		if (data->infile_fd >= 0)
			close(data->infile_fd);
		if (data->outfile_fd >= 0)
			close(data->outfile_fd);
		execve(cmd->cmd, cmd->args, envp);
	}
	return (child);
}

t_fds	init_fds(int pipe_fds[2], int in_fd)
{
	int	pipe_res;

	pipe_res = pipe(pipe_fds);
	if (pipe_res == -1)
		return ((t_fds){\
		.in = -1, \
		.out = -1, \
		.no = -1 \
	});
	return ((t_fds){\
		.in = in_fd, \
		.out = pipe_fds[1], \
		.no = pipe_fds[0] \
	});
}

t_fds	update_fds(t_fds fds, int pipe_fds[2])
{
	int	new_pipe_fds[2];
	int	pipe_res;

	pipe_res = pipe(new_pipe_fds);
	if (!pipe_fds || pipe_res == -1)
	{
		close(fds.in);
		close(pipe_fds[1]);
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	}
	close(fds.in);
	fds.in = pipe_fds[0];
	fds.out = new_pipe_fds[1];
	fds.no = new_pipe_fds[0];
	close(pipe_fds[1]);
	pipe_fds[0] = new_pipe_fds[0];
	pipe_fds[1] = new_pipe_fds[1];
	return (fds);
}

t_fds	end_update_fds(int pipe_fds[2], int out_fd)
{
	if (!pipe_fds)
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	return ((t_fds){\
		.in = pipe_fds[0], \
		.out = out_fd, \
		.no = pipe_fds[1] \
	});
}
