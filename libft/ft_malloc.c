/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:10 by algultse          #+#    #+#             */
/*   Updated: 2024/03/18 16:52:29 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_free(t_malloc *m, size_t index)
{
	if (m == NULL || index >= m->len || m->mallocs == NULL)
		return ;
	free(m->mallocs[index]);
	while (index < m->len - 1)
	{
		m->mallocs[index] = m->mallocs[index + 1];
		index++;
	}
	m->mallocs[index] = NULL;
	m->len--;
}

void	ft_free_all(t_malloc *m)
{
	if (m == NULL)
		return ;
	if (m->mallocs == NULL)
	{
		free(m);
		return ;
	}
	while (m->len > 0)
		free(m->mallocs[--(m->len)]);
	free(m->mallocs);
	free(m);
}

void	*ft_malloc(t_malloc *m, int blocks)
{
	void	*new_block;

	if (!m)
		m = init_malloc();
	if (m == NULL || blocks <= 0)
		return (NULL);
	new_block = malloc(blocks);
	if (new_block == NULL)
	{
		ft_free_all(m);
		exit(1);
	}
	m->mallocs = malloc_realloc(m);
	if (m->mallocs == NULL)
	{
		free(new_block);
		ft_free_all(m);
		exit(1);
	}
	m->mallocs[m->len] = new_block;
	m->len++;
	return (new_block);
}

void	*ft_malloc_with_index(t_malloc *m, int blocks, size_t *index)
{
	void	*new_block;

	new_block = ft_malloc(m, blocks);
	if (new_block == NULL)
		exit(1);
	*index = ft_malloc_get_index(m);
	return (new_block);
}

t_malloc	*init_malloc(void)
{
	t_malloc	*m;

	m = (t_malloc *)malloc(sizeof(t_malloc));
	if (m == NULL)
		exit(1);
	m->mallocs = NULL;
	m->len = 0;
	return (m);
}
