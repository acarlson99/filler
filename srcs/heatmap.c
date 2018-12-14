/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:37:09 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 22:56:45 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	set_map_val(t_filler *info, int x, int y)
{
	if (x + 1 < info->board_w && info->heatmap[y][x + 1] == OP)
		info->heatmap[y][x] = 1;
	if (y + 1 < info->board_h && info->heatmap[y + 1][x] == OP)
		info->heatmap[y][x] = 1;
	if (x + 1 < info->board_w && y + 1 < info->board_h &&
			info->heatmap[y + 1][x + 1] == OP)
		info->heatmap[y][x] = 1;
	if (x + 1 < info->board_w && y - 1 >= 0
		&& info->heatmap[y - 1][x + 1] == OP)
		info->heatmap[y][x] = 1;
	if (x - 1 >= 0 && info->heatmap[y][x - 1] == OP)
		info->heatmap[y][x] = 1;
	if (y - 1 >= 0 && info->heatmap[y - 1][x] == OP)
		info->heatmap[y][x] = 1;
	if (x - 1 >= 0 && y - 1 >= 0 && info->heatmap[y - 1][x - 1] == OP)
		info->heatmap[y][x] = 1;
	if (x - 1 >= 0 && y + 1 < info->board_h
		&& info->heatmap[y + 1][x - 1] == OP)
		info->heatmap[y][x] = 1;
}

void	toast_that_bad_boy(t_filler *info)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	while (y < info->board_h)
	{
		while (x < info->board_w)
		{
			if (info->heatmap[y][x] == 0)
				set_map_val(info, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}

void	put_heat(t_filler *info, int i, int x, int y)
{
	if (x + 1 < info->board_w && info->heatmap[y][x + 1] == i)
		info->heatmap[y][x] = i + 1;
	if (y + 1 < info->board_h && info->heatmap[y + 1][x] == i)
		info->heatmap[y][x] = i + 1;
	if (x + 1 < info->board_w && y + 1 < info->board_h\
		&& info->heatmap[y + 1][x + 1] == i)
		info->heatmap[y][x] = i + 1;
	if (x + 1 < info->board_w && y - 1 >= 0 && info->heatmap[y - 1][x + 1] == i)
		info->heatmap[y][x] = i + 1;
	if (x - 1 >= 0 && info->heatmap[y][x - 1] == i)
		info->heatmap[y][x] = i + 1;
	if (y - 1 >= 0 && info->heatmap[y - 1][x] == i)
		info->heatmap[y][x] = i + 1;
	if (x - 1 >= 0 && y - 1 >= 0 && info->heatmap[y - 1][x - 1] == i)
		info->heatmap[y][x] = i + 1;
	if (x - 1 >= 0 && y + 1 < info->board_h && info->heatmap[y + 1][x - 1] == i)
		info->heatmap[y][x] = i + 1;
}

void	spread_heat(t_filler *info)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 1;
	while (i < info->board_w)
	{
		while (y < info->board_h)
		{
			while (x < info->board_w)
			{
				if (info->heatmap[y][x] == 0)
					put_heat(info, i, x, y);
				x++;
			}
			x = 0;
			y++;
		}
		x = 0;
		y = 0;
		i++;
	}
}

void	fill_heatmap(t_filler **info)
{
	int		y;
	int		x;

	y = 0;
	while ((*info)->heatmap[y])
	{
		x = 0;
		while (x < (*info)->board_w)
		{
			if (TOUPPER((*info)->board[y][x]) == (*info)->me)
				(*info)->heatmap[y][x] = -2;
			else if (TOUPPER((*info)->board[y][x]) == (*info)->op)
				(*info)->heatmap[y][x] = -1;
			x++;
		}
		y++;
	}
	toast_that_bad_boy(*info);
	spread_heat(*info);
}
