/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:07:40 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/04 17:12:01 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** NOTE: This does not balance the tree well enough
** TODO: Fix this
*/

void		ft_btreeadd(t_btree **anode, t_btree *new,\
						int (*cmp)(t_btree *a, t_btree *b))
{
	t_btree		*node;

	node = *anode;
	while (node)
	{
		if (!node->left)
		{
			node->left = new;
			return ;
		}
		else if (!node->right)
		{
			node->right = new;
			return ;
		}
		else if (cmp(node->left, node->right))
			node = node->right;
		else
			node = node->left;
	}
}
