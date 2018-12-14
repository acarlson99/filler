/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreedel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:52:00 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/04 17:05:55 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_btreedel(t_btree **anode, void (*del)(void *, size_t))
{
	if ((*anode)->left)
		ft_btreedel(&((*anode)->left), del);
	if ((*anode)->right)
		ft_btreedel(&((*anode)->right), del);
	ft_btreedelone(anode, del);
}
