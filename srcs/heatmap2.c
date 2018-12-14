/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 22:56:09 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 22:56:21 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	make_heatmap(t_filler **info)
{
	const char	**ptr;
	int			y;

	ptr = (const char **)(*info)->board;
	y = 0;
	(*info)->heatmap = (int **)ft_memalloc(((*info)->board_h + 1)\
										* sizeof(int *));
	while (ptr[y])
	{
		(*info)->heatmap[y] = ft_memalloc((*info)->board_w * sizeof(int));
		y++;
	}
	ptr[y] = NULL;
}
