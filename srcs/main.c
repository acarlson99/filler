/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:18:05 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/12 00:18:53 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void	print_heatmap(t_filler **info)
{
	int		x;
	int		y;

	y = 0;
	while ((*info)->heatmap[y])
	{
		x = 0;
		while (x < (*info)->board_w)
		{
			ft_printf("%-3d ", (*info)->heatmap[y][x]);
			x++;
		}
		y++;
		ft_printf("\n");
	}
}

void	print_map(t_filler **info)
{
	int		lines;

	RET_NONE(!(*info)->board);
	lines = 0;
	while ((*info)->board[lines])
	{
		ft_putendl((*info)->board[lines]);
		lines++;
	}
}

void	print_piece(t_filler **info)
{
	int		lines;

	RET_NONE(!(*info)->piece);
	lines = 0;
	while ((*info)->piece[lines])
	{
		ft_putendl((*info)->piece[lines]);
		lines++;
	}
}

void	print_info(t_filler *info, int n)
{
	if (n)
		ft_printf("Oh fuck\n");
	ft_printf("\n\
Filename    : %s\n\
Player      : %d\n\
Board height: %d\n\
Board width : %d\n\
Piece height: %d\n\
Piece width : %d\n\
me			: %c\n\
op			: %c\n\
turn		: %d\n",\
			info->filename, info->player, info->board_h,\
			info->board_w, info->piece_h, info->piece_w,\
			info->me, info->op, info->turn);
	print_map(&info);
	print_piece(&info);
	print_heatmap(&info);
}

int		main(int argc, char **argv)
{
	t_filler	*info;
	int			n;

	(void)argc;
	RET_IF(!(info = (t_filler *)malloc(sizeof(t_filler))), 1);
	init_struct(&info);
	while (1)
	{
		n = populate_struct(argv, &info);
		if (n)
		{
			free_struct(&info);
			return (1);
		}
		solve_map(info);
		reset_struct(&info);
	}
	free_struct(&info);
}
