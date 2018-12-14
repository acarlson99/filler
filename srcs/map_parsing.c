/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:13:03 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 23:50:20 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				free_heatmap(t_filler **info)
{
	int		line;

	RET_IF(!(*info)->heatmap, 1);
	line = 0;
	while ((*info)->heatmap[line])
	{
		free((*info)->heatmap[line]);
		line++;
	}
	free((*info)->heatmap);
	(*info)->heatmap = NULL;
	return (1);
}

int				free_map(t_filler **info)
{
	int		line;

	RET_IF(!(*info)->board, 1);
	line = 0;
	while ((*info)->board[line])
	{
		free((*info)->board[line]);
		line++;
	}
	free((*info)->board);
	(*info)->board = NULL;
	return (1);
}

static int		check_line(char *str, int line, int line_len)
{
	RET_IF(TOCHAR(line / 100 % 10) != str[0], 1);
	RET_IF(TOCHAR(line / 10 % 10) != str[1], 1);
	RET_IF(TOCHAR(line % 10) != str[2] || str[3] != ' ', 1);
	RET_IF(str[3] != ' ', 1);
	str += 4;
	line = 0;
	while (str[line] && line < line_len)
	{
		RET_IF(!ft_isin(str[line], ".OoXx"), 1);
		line++;
	}
	return (str[line] || line != line_len);
}

int				parse_map(t_filler **info)
{
	int		lines;
	int		n;

	lines = 0;
	n = 0;
	RET_IF(!((*info)->board = (char **)malloc(sizeof(char *)
											* ((*info)->board_h) + 8)), 1);
	while (lines < (*info)->board_h
			&& get_next_line(FT_STDIN_FILENO, &(*info)->line) > 0)
	{
		if (check_line((*info)->line, lines, (*info)->board_w))
		{
			n = 1;
			free((*info)->line);
			break ;
		}
		(*info)->board[lines] = ft_strdup((*info)->line + 4);
		free((*info)->line);
		lines++;
	}
	(*info)->board[lines] = NULL;
	DO_IF(n, free_map(info));
	return (n);
}
