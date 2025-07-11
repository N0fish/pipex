/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:16 by algultse          #+#    #+#             */
/*   Updated: 2024/03/22 12:22:40 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	**malloc_realloc(t_malloc *m)
{
	void	**new_mallocs;
	size_t	i;

	new_mallocs = malloc(sizeof(void *) * (m->len + 1));
	if (new_mallocs == NULL)
		return (NULL);
	i = 0;
	while (i < m->len && m->mallocs)
	{
		new_mallocs[i] = m->mallocs[i];
		i++;
	}
	if (m->mallocs)
		free(m->mallocs);
	return (new_mallocs);
}

void	ft_free_last(t_malloc *m)
{
	ft_free(m, ft_malloc_get_index(m));
	m->len--;
}

size_t	ft_malloc_get_index(t_malloc *m)
{
	if (m->len == 0)
		return (0);
	return (m->len - 1);
}
