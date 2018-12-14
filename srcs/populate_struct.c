/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:28:55 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 23:33:48 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	init_struct(t_filler **info)
{
	(*info)->me = 0;
	(*info)->op = 0;
	(*info)->line = NULL;
	(*info)->filename = NULL;
	(*info)->board = NULL;
	(*info)->piece = NULL;
	(*info)->heatmap = NULL;
	(*info)->player = 0;
	(*info)->board_h = 0;
	(*info)->board_w = 0;
	(*info)->piece_h = 0;
	(*info)->piece_w = 0;
	(*info)->fname_len = 0;
	(*info)->turn = 0;
	(*info)->moves = NULL;
}

int		first_three(t_filler **info)
{
	int		n;

	if (!(*info)->turn)
	{
		n = line_one(info);
		free((*info)->line);
		RET_IF(n, n);
		(*info)->me = ((*info)->player == 1 ? 'O' : 'X');
		(*info)->op = ((*info)->player == 1 ? 'X' : 'O');
	}
	n = line_two(info);
	RET_IF(n, n);
	free((*info)->line);
	n = line_three(info);
	RET_IF(n, n);
	free((*info)->line);
	return (0);
}

int		populate_struct(char **argv, t_filler **info)
{
	int		i;

	i = 0;
	if (!(*info)->turn)
	{
		(*info)->filename = ft_strdup(argv[0]);
		(*info)->fname_len = ft_strlen((*info)->filename);
	}
	RET_IF(first_three(info), 1);
	RET_IF(parse_map(info), free_map(info));
	RET_IF(parse_piece(info), free_map(info));
	make_heatmap(info);
	fill_heatmap(info);
	(*info)->turn = 1;
	return (0);
}

void	reset_struct(t_filler **info)
{
	DO_IF((*info)->board, free_map(info));
	(*info)->board = NULL;
	DO_IF((*info)->piece, free_piece(info));
	(*info)->piece = NULL;
	DO_IF((*info)->heatmap, free_heatmap(info));
	(*info)->heatmap = NULL;
	DO_IF((*info)->moves, ft_mlstdel(&(*info)->moves));
	(*info)->moves = NULL;
	(*info)->piece_h = 0;
	(*info)->piece_w = 0;
}

void	free_struct(t_filler **info)
{
	RET_NONE(!*info);
	if ((*info)->filename)
	{
		free((*info)->filename);
		(*info)->filename = NULL;
	}
	ft_mlstdel(&(*info)->moves);
	free_map(info);
	free_piece(info);
	free_heatmap(info);
	free(*info);
	*info = NULL;
}
