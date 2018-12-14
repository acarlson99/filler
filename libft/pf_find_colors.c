/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_find_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:26:41 by acarlson          #+#    #+#             */
/*   Updated: 2018/11/18 17:43:13 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char		*g_pf_colors[] =
{
	"nc",
	"fg_red",
	"fg_green",
	"fg_blue",
	"fg_white",
	"fg_black",
	"bg_red",
	"bg_green",
	"bg_blue",
	"bg_white",
	"bg_black",
	NULL
};

char		*g_pf_codes[] =
{
	NC,
	FG_RED,
	FG_GRN,
	FG_BLU,
	FG_WHT,
	FG_BLK,
	BG_RED,
	BG_GRN,
	BG_BLU,
	BG_WHT,
	BG_BLK,
};

int			pf_find_colors(const char *s, int *count)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strcspn(s, "}");
	str = ft_strndup(s, len);
	i = -1;
	while (g_pf_colors[++i])
	{
		if (!(ft_strcmp(str, g_pf_colors[i])))
		{
			ft_putstr_fd(g_pf_codes[i], PF_FD);
			free(str);
			return (len + 1);
		}
	}
	*count = *count + ft_putnstr_fd((char *)s - 1, len + 2, PF_FD);
	free(str);
	return (len + 1);
}
