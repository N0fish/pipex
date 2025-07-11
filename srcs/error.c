/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:31:05 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 11:51:15 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_pipex(char *str)
{
	if (str)
		ft_printf("%s", str);
	exit(EXIT_FAILURE);
}

void	error_pipex(char *str)
{
	if (str)
		perror(str);
	exit(EXIT_FAILURE);
}

void	error_free_exit(t_data *data, char *str)
{
	if (data)
	{
		if (data->infile_fd > 0)
			close(data->infile_fd);
		if (data->outfile_fd > 0)
			close(data->outfile_fd);
		free_data(data);
	}
	error_pipex(str);
}
