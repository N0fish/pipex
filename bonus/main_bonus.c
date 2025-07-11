/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:17:40 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 13:22:10 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_redirect(char *limiter, int fd)
{
	char	*line;

	ft_printf("here_doc> ");
	line = get_next_line(0);
	if (!line)
		return ;
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			get_next_line(FREE_STATIC_FD);
			close(fd);
			return ;
		}
		ft_printf("here_doc> ");
		write (fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
}

void	handle_here_doc(t_data *data)
{
	int		pipe_fds[2];

	if (!data->here_doc)
		return ;
	if (pipe(pipe_fds) == -1)
		error_free_exit(data, "Error creating pipe");
	input_redirect(data->limiter, pipe_fds[1]);
	close(pipe_fds[1]);
	data->infile_fd = pipe_fds[0];
}

void	wait_clean_up(int pipe_fds[2], t_data *data)
{
	t_cmd	*cmds;

	close(pipe_fds[0]);
	close(pipe_fds[1]);
	cmds = data->cmd;
	while (cmds)
	{
		data->exec_error = false;
		if ((cmds->pid > -1 && waitpid(cmds->pid, &data->wtpd, 0) == -1) \
			|| cmds->pid == -1)
			data->exec_error = true;
		cmds = cmds->next;
	}
	if (data->infile_fd > -1)
		close(data->infile_fd);
	if (data->outfile_fd > -1)
		close(data->outfile_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	child_process(t_data *data, char **envp)
{
	int		pipe_fds[2];
	t_fds	fds;
	t_cmd	*cmds;

	cmds = data->cmd;
	fds = init_fds(pipe_fds, data->infile_fd);
	if (fds.in == -1 && fds.out == -1 && fds.no == -1)
		error_free_exit(data, "Error creating pipe");
	cmds->pid = exec_child(fds, data, cmds, envp);
	cmds = cmds->next;
	while (cmds && cmds->next)
	{
		fds = update_fds(fds, pipe_fds);
		if (fds.in == -1 && fds.out == -1 && fds.no == -1)
			error_free_exit(data, "Error creating pipe");
		cmds->pid = exec_child(fds, data, cmds, envp);
		cmds = cmds->next;
	}
	close(fds.in);
	fds = end_update_fds(pipe_fds, data->outfile_fd);
	if (fds.in == -1 && fds.out == -1 && fds.no == -1)
		error_free_exit(data, "Error creating pipe");
	cmds->pid = exec_child(fds, data, cmds, envp);
	wait_clean_up(pipe_fds, data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		exit_code;

	if (argc < 5)
		exit_pipex("Error: too few arguments\n");
	data = init_data(argc, argv, envp);
	handle_here_doc(data);
	child_process(data, envp);
	exit_code = main_exit(data);
	free_data(data);
	return (exit_code);
}
