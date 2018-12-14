/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:29:44 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 22:23:41 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		is_valid(t_filler *info, int x, int y)
{
	int		p_x;
	int		p_y;
	int		overlap;

	p_y = -1;
	overlap = 0;
	RET_IF(x + info->piece_w > info->board_w
			|| y + info->piece_h > info->board_h, 0);
	while (info->piece[++p_y])
	{
		p_x = -1;
		while (info->piece[p_y][++p_x])
		{
			if (info->piece[p_y][p_x] == '*')
			{
				RET_IF(TOUPPER(info->board[y + p_y][x + p_x]) == UCHO, 0);
				if (TOUPPER(info->board[y + p_y][x + p_x]) == UCHM)
				{
					RET_IF(overlap, 0);
					overlap++;
				}
			}
		}
	}
	return (overlap == 1);
}

void	place_piece(t_filler *info, int x, int y)
{
	int		p_x;
	int		p_y;

	p_y = 0;
	while (info->piece[p_y])
	{
		p_x = 0;
		while (info->piece[p_y][p_x])
		{
			if (info->piece[p_y][p_x] == '*')
			{
				info->board[y + p_y][x + p_x] = LCHM;
			}
			p_x++;
		}
		p_y++;
	}
}

void	find_optimal_move(t_filler *info)
{
	int			big_y;
	int			big_x;
	int			big_score;
	t_mvlist	*ptr;

	DO_IF(!info->moves, ft_printf("0 0\n"));
	RET_NONE(!info->moves);
	big_y = 0;
	big_x = 0;
	big_score = FT_INT_MAX;
	ptr = info->moves;
	while (ptr)
	{
		if (ptr->score < big_score && ptr->score > -2)
		{
			big_y = ptr->y;
			big_x = ptr->x;
			big_score = ptr->score;
		}
		ptr = ptr->next;
	}
	big_y = (info && big_score == FT_INT_MAX) ? info->moves->y : big_y;
	big_x = (info && big_score == FT_INT_MAX) ? info->moves->x : big_x;
	ft_printf("%d %d\n", big_y, big_x);
}

int		find_score(t_filler *info, int y, int x)
{
	int		p_y;
	int		p_x;
	int		total;

	total = 0;
	p_y = 0;
	while (p_y < info->piece_h)
	{
		p_x = 0;
		while (p_x < info->piece_w)
		{
			if (info->piece[p_y][p_x] == '*')
				total += info->heatmap[p_y + y][p_x + x];
			p_x++;
		}
		p_y++;
	}
	return (total);
}

void	solve_map(t_filler *info)
{
	int		x;
	int		y;

	y = 0;
	while (y <= info->board_h - info->piece_h)
	{
		x = 0;
		while (x <= info->board_w - info->piece_w)
		{
			if (is_valid(info, x, y))
				ft_mlstadd(&info->moves,
							ft_mlstnew(find_score(info, y, x), y, x));
			x++;
		}
		y++;
	}
	find_optimal_move(info);
}
