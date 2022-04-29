/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:27:27 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 11:04:07 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		nxt_step(t_scn *scn);
void	update_grid(t_scn *scn);
void	swap_grids(t_scn *scn);
void	comp_nxt(t_scn *scn, int width, int hight);

int	nxt_step(t_scn *scn)
{
	update_grid(scn);
	//for( int i = 0 ; i < 5; i++)
	rotate(-1, scn);
	swap_grids(scn);
	comp_nxt(scn, ft_lstsize(scn->grid->content), ft_lstsize(scn->grid));
	return (0);
}

void	update_grid(t_scn *scn)
{
	int		i;
	int		j;
	t_list	*pt;
	t_list	*line;

	i = 0;
	line = scn->grid;
	while (line)
	{
		j = 0;
		pt = (line->content);
		while (pt)
		{
			((t_pnt *)(pt->content))->z = (scn->now)[i][j];
			((t_pnt *)(pt->content))->color = 0x00ff80;
			if (((t_pnt *)(pt->content))->z > 0)
				((t_pnt *)(pt->content))->color = 0xff8000;
			else if (((t_pnt *)(pt->content))->z < 0)
				((t_pnt *)(pt->content))->color = 0x0080ff;
			j++;
			pt = pt->next;
		}
		i++;
		line = line->next;
	}
}

void	swap_grids(t_scn *scn)
{
	float	**temp;

	temp = scn->now;
	scn->now = scn->nxt;
	scn->nxt = temp;
}

void	boundary(t_scn *scn, int ij[2], int wh[2], float sxy[2])
{
	int	hight;
	int	width;
	int	i;
	int	j;

	i = ij[0];
	j = ij[1];
	hight = wh[1];
	width = wh[0];
	if (i == 0)
		(scn->nxt)[i][j] += sxy[1] * 2 * ((scn->now)[i + 1][j]);
	else if (i == hight - 1)
		(scn->nxt)[i][j] += sxy[1] * 2 * ((scn->now)[i - 1][j]);
	else
		(scn->nxt)[i][j]
			+= sxy[1] * ((scn->now)[i - 1][j] + (scn->now)[i + 1][j]);
	if (j == 0)
		(scn->nxt)[i][j] += sxy[0] * 2 * ((scn->now)[i][j + 1]);
	else if (j == width - 1)
		(scn->nxt)[i][j] += sxy[0] * 2 * ((scn->now)[i][j - 1]);
	else
		(scn->nxt)[i][j]
			+= sxy[0] * ((scn->now)[i][j - 1] + (scn->now)[i][j + 1]);
}

void	comp_nxt(t_scn *scn, int width, int hight)
{
	int		wh[2];
	int		ij[2];
	float	sxy[2];

	sxy[0] = STABILITY * (1 + (hight == 1)) * (width != 1);
	sxy[1] = STABILITY * (1 + (width == 1)) * (hight != 1);
	wh[0] = width;
	wh[1] = hight;
	ij[0] = -1;
	while (++ij[0] < hight)
	{
		ij[1] = -1;
		while (++ij[1] < width)
		{
			(scn->nxt)[ij[0]][ij[1]] = 2 * (1 - sxy[0] - sxy[1]) * ((scn->now)
				[ij[0]][ij[1]]) - (scn->nxt)[ij[0]][ij[1]];
			if (ij[0] * ij[1] == 0 || ij[0] == hight - 1 || ij[1] == width - 1)
				boundary(scn, ij, wh, sxy);
			else
			(scn->nxt)[ij[0]][ij[1]] += (sxy[0]) * ((scn->now)
					[ij[0]][ij[1] - 1] + (scn->now)[ij[0]][ij[1] + 1])
					+ (sxy[1]) * ((scn->now)[ij[0] - 1][ij[1]]
						+ (scn->now)[ij[0] + 1][ij[1]]);
		}
	}
}

// void	comp_nxt(t_scn *scn, int width, int hight)
// {
// 	int		i;
// 	int		j;
// 	float	sxy[2];	

// 	sxy[0] = STABILITY * (1 + (hight == 1)) * (width != 1);
// 	sxy[1] = STABILITY * (1 + (width == 1)) * (hight != 1);
// 	i = 0;
// 	while (i < hight)
// 	{
// 		j = 0;
// 		while (j < width)
// 		{
// 			if (i == 0 || j == 0 || i == hight - 1 || j == width - 1)
// 			{
// 				(scn->nxt)[i][j] = 2 * (1 - sxy[0] - sxy[1]) * ((scn->now)[i][j]) - (scn->nxt)[i][j];
// 				if (i == 0)
// 					(scn->nxt)[i][j] += sxy[1] * 2 * ((scn->now)[i + 1][j]);
// 				else if (i == hight - 1)
// 					(scn->nxt)[i][j] += sxy[1] * 2 * ((scn->now)[i - 1][j]);
// 				else
// 					(scn->nxt)[i][j] += sxy[1] * ((scn->now)[i - 1][j] + (scn->now)[i + 1][j]);
// 				if (j == 0)
// 					(scn->nxt)[i][j] += sxy[0] * 2 * ((scn->now)[i][j + 1]);
// 				else if (j == width - 1)
// 					(scn->nxt)[i][j] += sxy[0] * 2 * ((scn->now)[i][j - 1]);
// 				else
// 					(scn->nxt)[i][j] += sxy[0] * ((scn->now)[i][j - 1] + (scn->now)[i][j + 1]);
// 			}
// 			else
// 				(scn->nxt)[i][j] = 
// 					(sxy[0]) * ((scn->now)[i][j - 1] + (scn->now)[i][j + 1])
// 					+ (sxy[1]) * ((scn->now)[i - 1][j] + (scn->now)[i + 1][j])
// 					+ 2 * (1 - sxy[0] - sxy[1]) * ((scn->now)[i][j]) - (scn->nxt)[i][j];
// 			++j;
// 		}
// 		++i;
// 	}
// }
