/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:33:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/04 15:52:45 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*ft_btreenew(void const *content, size_t content_size)
{
	t_btree		*new;

	NULL_CHECK(!(new = (t_btree *)malloc(sizeof(t_btree))));
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = (void *)malloc((content_size) * (sizeof(void *)))))
		{
			free(new);
			return (NULL);
		}
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->left = NULL;
	new->right = NULL;
	return (new);
}
