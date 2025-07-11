/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:03:32 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 12:03:01 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_fds {
	int	in;
	int	out;
	int	no;
}				t_fds;

typedef struct s_cmd {
	char			*cmd;
	char			**args;
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data {
	int				infile_fd;
	int				outfile_fd;
	char			**envp;
	char			**res_path;
	struct s_cmd	*cmd;
	bool			here_doc;
	char			*limiter;
	int				wtpd;
	bool			exec_error;
	int				i;
}				t_data;

/* error */
void	exit_pipex(char *str);
void	error_pipex(char *str);
void	error_free_exit(t_data *data, char *str);
/**/
t_data	*init_data(int argc, char **argv, char **envp);
void	child_process(t_data *data, char **envp);
/* free */
int		main_exit(t_data *data);
void	free_data(t_data *data);
void	free_cmd_argv(char **cmd_argv);
/* cmd */
t_cmd	*new_cmd(char *cmd, char **args);
bool	add_cmd(t_cmd **cmds, t_cmd *new);
char	**split_cmd_argv(char *argv, char **res_path, char **data_cmd);
/* process */
pid_t	exec_child(t_fds fds, t_data *data, t_cmd *cmd, char **envp);
t_fds	init_fds(int pipe_fds[2], int in_fd);
t_fds	update_fds(t_fds fds, int pipe_fds[2]);
t_fds	end_update_fds(int pipe_fds[2], int out_fd);

#endif