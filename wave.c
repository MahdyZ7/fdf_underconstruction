/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:08:23 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 11:04:16 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	int_spc1(t_scn *scn, int width, int hight);
void	int_spc2(t_scn *scn, int width, int hight);
void	setup_spc(t_scn *scn);

void	setup_spc(t_scn *scn)
{
	int	width;
	int	hight;
	int	i;

	width = ft_lstsize(scn->grid->content);
	hight = ft_lstsize(scn->grid);
	scn->now = malloc(sizeof(*(scn->now)) * hight);
	scn->nxt = malloc(sizeof(*(scn->now)) * hight);
	i = 0;
	while (i < hight)
	{
		(scn->now)[i] = malloc(sizeof(**(scn->now)) * width);
		(scn->nxt)[i] = malloc(sizeof(**(scn->now)) * width);
		++i;
	}
	int_spc1(scn, width, hight);
}

void	int_spc1(t_scn *scn, int width, int hight)
{
	int		i;
	int		j;
	t_list	*line;
	t_list	*point;

	i = 0;
	line = scn->grid;
	while (line)
	{
		j = 0;
		point = line->content;
		while (point)
		{
			(scn->now)[i][j] = ((t_pnt *)(point->content))->z;
			point = point->next;
			++j;
		}
		line = line->next;
		++i;
	}
	int_spc2(scn, width, hight);
}

static void	row_bounds(t_scn *scn, int hight, int width, float sxy[2])
{
	int	row;
	int	col;

	row = 0;
	while (row < hight)
	{
		col = -1;
		while (++col < width)
		{
			(scn->nxt)[row][col]
				= (1 - 2 * sxy[0] - 2 * sxy[1]) * ((scn->now)[row][col]);
			if (row == 0 && row + 1 < hight)
				(scn->nxt)[row][col] += sxy[1] * 2 * ((scn->now)[row + 1][col]);
			else if (row == hight - 1 && row - 1 >= 0)
				(scn->nxt)[row][col] += sxy[1] * 2 * ((scn->now)[row - 1][col]);
			if (col == 0 && col + 1 < width)
				(scn->nxt)[row][col] += sxy[0] * 2 * ((scn->now)[row][col + 1]);
			else if (col == width - 1 && col - 1 >= 0)
				(scn->nxt)[row][col] += sxy[0] * 2 * ((scn->now)[row][col - 1]);
			else if (col != 0 && col != width - 1)
				(scn->nxt)[row][col] += sxy[0]
					* ((scn->now)[row][col - 1] + (scn->now)[row][col + 1]);
		}
		row += (hight == 1) + hight - 1;
	}
}

static void	col_bounds(t_scn *scn, int hight, int width, float sxy[2])
{
	int	row;
	int	col;

	col = 0;
	while (col < width)
	{
		row = 0;
		while (++row < hight - 1)
		{
			(scn->nxt)[row][col]
				= (1 - 2 * sxy[0] - 2 * sxy[1]) * ((scn->now)[row][col]);
			if (row - 1 >= 0 && row + 1 < hight)
				(scn->nxt)[row][col] += sxy[1]
					* ((scn->now)[row - 1][col] + (scn->now)[row + 1][col]);
			if (col == 0 && col + 1 < width)
				(scn->nxt)[row][col] += sxy[0] * 2 * ((scn->now)[row][col + 1]);
			else if (col == width - 1 && col - 1 >= 0)
				(scn->nxt)[row][col] += sxy[0] * 2 * ((scn->now)[row][col - 1]);
		}
		col += (width == 1) + width - 1;
	}
}

void	int_spc2(t_scn *scn, int width, int hight)
{
	int		row;
	int		col;
	float	sxy[2];	

	sxy[0] = STABILITY / 2 * (1 + (hight == 1)) * (width != 1);
	sxy[1] = STABILITY / 2 * (1 + (width == 1)) * (hight != 1);
	printf ("The constants are sx: %.20f sy: %.20f\n", sxy[0] * 2, sxy[1] * 2);
	row = 0;
	row_bounds(scn, hight, width, sxy);
	col_bounds(scn, hight, width, sxy);
	while (++row < hight - 1)
	{
		col = 0;
		while (++col < width - 1)
		{
			(scn->nxt)[row][col]
				= sxy[0] * ((scn->now)[row][col - 1] + (scn->now)[row][col + 1])
				+ sxy[1] * ((scn->now)[row - 1][col] + (scn->now)[row + 1][col])
				+ (1 - 2 * sxy[0] - 2 * sxy[1]) * ((scn->now)[row][col]);
		}
	}
}
