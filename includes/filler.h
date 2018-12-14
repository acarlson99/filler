/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:23:23 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/11 23:32:50 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define LCHM TOLOWER(info->me)
# define LCHO TOLOWER(info->op)
# define UCHM TOUPPER(info->me)
# define UCHO TOUPPER(info->op)

# define OP -1
# define EN -1
# define ME -2

typedef struct	s_mvlist
{
	int					score;
	int					y;
	int					x;
	struct s_mvlist		*next;
}				t_mvlist;

typedef struct	s_filler
{
	char		me;
	char		op;
	char		*line;
	char		*filename;
	char		**board;
	char		**piece;
	int			**heatmap;
	int			player;
	int			board_h;
	int			board_w;
	int			piece_h;
	int			piece_w;
	size_t		fname_len;
	size_t		turn;
	t_mvlist	*moves;
}				t_filler;

int				populate_struct(char **argv, t_filler **info);
void			reset_struct(t_filler **info);
void			free_struct(t_filler **info);
void			init_struct(t_filler **info);

int				line_one(t_filler **info);
int				line_two(t_filler **info);
int				line_three(t_filler **info);

int				parse_map(t_filler **info);
int				parse_piece(t_filler **info);
int				free_piece(t_filler **info);
int				free_map(t_filler **info);
int				free_heatmap(t_filler **info);

void			solve_map(t_filler *info);

t_mvlist		*ft_mlstnew(int score, int x, int y);
void			ft_mlstadd(t_mvlist **alst, t_mvlist *new);
void			ft_mlstdelone(t_mvlist **alst);
void			ft_mlstdel(t_mvlist **alst);

void			print_map(t_filler **info);

void			fill_heatmap(t_filler **info);
void			make_heatmap(t_filler **info);

#endif
