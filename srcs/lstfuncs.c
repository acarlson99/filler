/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 20:40:18 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 22:39:32 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_mvlist		*ft_mlstnew(int score, int y, int x)
{
	t_mvlist	*new;

	NULL_CHECK(!(new = (t_mvlist *)malloc(sizeof(t_mvlist))));
	new->score = score;
	new->y = y;
	new->x = x;
	new->next = NULL;
	return (new);
}

void			ft_mlstadd(t_mvlist **alst, t_mvlist *new)
{
	new->next = *alst;
	*alst = new;
}

void			ft_mlstdelone(t_mvlist **alst)
{
	free(*alst);
	*alst = NULL;
}

void			ft_mlstdel(t_mvlist **alst)
{
	t_mvlist		*next;

	while (*alst)
	{
		next = (*alst)->next;
		ft_mlstdelone(alst);
		*alst = next;
	}
}
