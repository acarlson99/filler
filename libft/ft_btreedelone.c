/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreedelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:39:21 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/04 16:49:23 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_btreedelone(t_btree **anode, void (*del)(void *, size_t))
{
	del((*anode)->content, (*anode)->content_size);
	free(*anode);
	*anode = NULL;
}
