/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:29:38 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 12:04:04 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_env_path(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	init_cmd(t_data *data, int argc, char **argv)
{
	char	*path;
	char	*cmd;
	char	**args;

	if (!data)
		return ;
	path = find_env_path(data->envp);
	if (!path)
		error_free_exit(data, "no path in env");
	data->res_path = ft_split(path, ':');
	if (!data->res_path)
		error_free_exit(data, "path not found");
	data->i = ft_ternary(data->here_doc, 3, 2) - 1;
	while ((++data->i) < argc - 1)
	{
		cmd = NULL;
		args = split_cmd_argv(argv[data->i], data->res_path, &cmd);
		if (!cmd)
			error_free_exit(data, "command error");
		if (!add_cmd(&data->cmd, new_cmd(cmd, args)) || !data->cmd)
		{
			free_cmd_argv(args);
			ft_printf("command not found: %s\n", argv[data->i]);
		}
	}
}

bool	init_here_doc_mode(t_data *data, char *here_doc, char *limiter)
{
	if (ft_strncmp(here_doc, "here_doc\0", 9) == 0)
	{
		data->limiter = limiter;
		return (1);
	}
	return (0);
}

t_data	*init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error_free_exit(data, "error malloc data");
	data->exec_error = false;
	data->here_doc = init_here_doc_mode(data, argv[1], argv[2]);
	if (data->here_doc)
		data->outfile_fd = open(argv[argc - 1], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		data->infile_fd = open(argv[1], O_RDONLY);
		if (data->infile_fd < 0)
			perror("Error opening infile");
		data->outfile_fd = open(argv[argc - 1], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (data->outfile_fd < 0)
		perror("Error opening outfile");
	data->envp = envp;
	data->wtpd = EXIT_SUCCESS;
	data->cmd = NULL;
	return (init_cmd(data, argc, argv), data);
}
