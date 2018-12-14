/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:12:57 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 23:25:58 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				line_free(char *str)
{
	free(str);
	return (1);
}

int				get_piece_size(t_filler **info)
{
	char	*str;

	RET_IF((get_next_line(FT_STDIN_FILENO, &(*info)->line)) <= 0, 1);
	str = (*info)->line;
	RET_IF(ft_strncmp(str, "Piece ", 6), line_free((*info)->line));
	str += 6;
	RET_IF(!ISDIGIT(*str), line_free((*info)->line));
	(*info)->piece_h = ft_atoi(str);
	WHILE_DO(ISDIGIT(*str), str++);
	RET_IF(*str != ' ', line_free((*info)->line));
	str++;
	RET_IF(!ISDIGIT(*str), line_free((*info)->line));
	(*info)->piece_w = ft_atoi(str);
	WHILE_DO(ISDIGIT(*str), str++);
	RET_IF(*str != ':', line_free((*info)->line));
	str++;
	RET_IF(*str, line_free((*info)->line));
	free((*info)->line);
	return (0);
}

static int		check_piece_line(char *str, int width)
{
	int		n;

	n = 0;
	while (str[n] && n < width)
	{
		RET_IF(str[n] != '.' && str[n] != '*', 1);
		n++;
	}
	return (!*str || n != width);
}

int				parse_piece(t_filler **info)
{
	int		lines;
	int		n;

	lines = 0;
	n = 0;
	RET_IF(get_piece_size(info), 1);
	RET_IF(!((*info)->piece = (char **)malloc(sizeof(char *)
											* ((*info)->piece_h) + 8)), 1);
	while (lines < (*info)->piece_h
			&& get_next_line(FT_STDIN_FILENO, &(*info)->line) > 0)
	{
		if (check_piece_line((*info)->line, (*info)->piece_w))
		{
			n = 1;
			break ;
		}
		(*info)->piece[lines] = ft_strdup((*info)->line);
		free((*info)->line);
		lines++;
	}
	(*info)->piece[lines] = NULL;
	DO_IF(n, free_map(info));
	return (n);
}

int				free_piece(t_filler **info)
{
	int		line;

	RET_IF(!((*info)->piece), 1);
	line = 0;
	while ((*info)->piece[line])
	{
		free((*info)->piece[line]);
		line++;
	}
	free((*info)->piece);
	(*info)->piece = NULL;
	return (1);
}
