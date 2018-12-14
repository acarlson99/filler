/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:38:47 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 22:35:56 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		line_one(t_filler **info)
{
	int		g;
	char	*str;

	RET_IF((*info)->turn, 0);
	g = get_next_line(FT_STDIN_FILENO, &(*info)->line);
	str = (*info)->line;
	RET_IF(g <= 0, 1);
	RET_IF(!ft_strnequ(str, "$$$ exec p", 10), 1);
	str += 10;
	(*info)->player = *str == '1'\
		|| *str == '2' ? *str - '0' : 0;
	RET_IF(!(*info)->player, 1);
	str++;
	RET_IF(!ft_strnequ(str, " : [", 4), 1);
	str += 4;
	RET_IF(!ft_strnequ(str, (*info)->filename, (*info)->fname_len), 1);
	str += (*info)->fname_len;
	RET_IF(str[0] != ']' || str[1] != '\0', 1);
	return (0);
}

int		line_two(t_filler **info)
{
	int		g;
	char	*str;

	g = get_next_line(FT_STDIN_FILENO, &(*info)->line);
	RET_IF(g <= 0, 1);
	str = (*info)->line;
	RET_IF(!ft_strnequ(str, "Plateau ", 8), 1);
	str += 8;
	(*info)->board_h = ft_atoi(str);
	while (ISDIGIT(*str))
		str++;
	IF_ELSE(*str == ' ', str++, RET_IF(1, 1));
	(*info)->board_w = ft_atoi(str);
	while (ISDIGIT(*str))
		str++;
	return (*str == ':' && !(str + 1));
}

int		line_three(t_filler **info)
{
	int		i;
	int		j;
	char	*str;

	RET_IF((get_next_line(FT_STDIN_FILENO, &(*info)->line)) <= 0, 1);
	str = (*info)->line;
	i = 0;
	j = 0;
	while (*str == ' ' && ++i)
		IF_ELSE(i <= 4, str++, RET_IF(1, 1));
	i = '0';
	while (*str)
	{
		if (*str == i && j < (*info)->board_w)
		{
			j++;
			i = i != '9' ? i + 1 : '0';
			str++;
		}
		ELSE_DO(RET_IF(1, 1));
	}
	return (j != (*info)->board_w || *str);
}
