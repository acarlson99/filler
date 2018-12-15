/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:18:05 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/14 22:56:28 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
