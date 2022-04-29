/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:06:31 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 15:41:45 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_grade(t_pnt *pt0, t_pnt *ptm, t_pnt *pt1)
{
	int		red;
	int		green;
	int		blue;
	float	dif;

	dif = sqrtf(powf(ptm->x - pt0->x, 2) + powf(ptm->y - pt0->y, 2));
	dif /= sqrtf(powf(pt1->x - pt0->x, 2) + powf(pt1->y - pt0->y, 2));
	red = (pt0->color) >> 16 & 255;
	green = (pt0->color) >> 8 & 255;
	blue = (pt0->color) & 255;
	red = red + (int)((((pt1->color) >> 16 & 255) - red) * dif);
	green = green + (int)((((pt1->color) >> 8 & 255) - green) * dif);
	blue = blue + (int)((((pt1->color) & 255) - blue) * dif);
	return ((red << 16) + (green << 8) + blue);
}

void	dl_helper(t_pnt *point0, t_pnt pointm, t_pnt *point1, t_img *img)
{
	double	dxy[2];
	double	sxy[2];
	double	error[2];

	dxy[0] = fabs((point1->x) * 1.0 - (pointm.x) * 1.0);
	sxy[0] = ((pointm.x) < (point1->x)) * 2.0 - 1.0;
	dxy[1] = -fabs((point1->y) * 1.0 - (pointm.y) * 1.0);
	sxy[1] = ((pointm.y) < (point1->y)) * 2.0 - 1.0;
	error[0] = dxy[0] + dxy[1];
	while (pointm.x != point1->x || pointm.y != point1->y)
	{
		pixel_put(img, pointm.x, pointm.y, pointm.color);
		error[1] = 2 * error[0];
		if (error[1] >= dxy[1] && pointm.x != point1->x)
		{
			error[0] += dxy[1];
			pointm.x += sxy[0];
		}
		if (error[1] <= dxy[0] && pointm.y != point1->y)
		{
			error[0] += dxy[0];
			pointm.y += sxy[1];
		}
		pointm.color = color_grade(point0, &pointm, point1);
	}
}

void	draw_line(t_list *line, t_img *img)
{
	t_list	*(pt[3]);

	while (line)
	{
		pt[0] = (line->content);
		pt[1] = (pt[0])->next;
		pt[2] = NULL;
		if (line->next)
			pt[2] = line->next->content;
		while (pt[0])
		{
			if (pt[1])
			{
				dl_helper(pt[0]->CNT, *(t_pnt *)(pt[0]->CNT), pt[1]->CNT, img);
				pt[1] = pt[1]->next;
			}
			if (pt[2])
			{
				dl_helper(pt[0]->content, *(t_pnt *)(pt[0]->content), pt[2]->content, img);
				pt[2] = pt[2]->next;
			}
			pt[0] = pt[0]->next;
		}
		line = line->next;
	}
}

void	set_pnt(t_pnt *point, t_img *img, int x_index, int y_index)
{
	int	tempz;

	// rotate and translate one at a time
		//Rz
	point->x = x_index * img->nums->cos_a + y_index * img->nums->sin_a;
	point->y = y_index * img->nums->cos_a - x_index * img->nums->sin_a;
		//Rx
	tempz = point->y * img->nums->sin_g
		+ point->z * img->nums->cos_g * img->nums->div;
	point->y = point->y * img->nums->cos_g
		- point->z * img->nums->sin_g * img->nums->div;
		//Ry
	point->x = (point->x) * img->nums->cos_b
		+ tempz * img->nums->sin_b;
}

void	draw_points(t_list *grid, t_img *img)
{
	t_list	*lst_point;
	t_pnt	*pnt;
	int		x_index;
	int		y_index;

	y_index = (0 - img->nums->hight / 2) * img->nums->div;
	put_border(img);
	while (grid)
	{
		lst_point = grid->content;
		x_index = (0 - img->nums->width / 2) * img->nums->div;
		while (lst_point)
		{
			pnt = lst_point->content;
			set_pnt(pnt, img, x_index, y_index);
			pnt->y += img->nums->y_trans;
			pnt->x += img->nums->x_trans;
			x_index += img->nums->div;
			pixel_put(img, pnt->x, pnt->y, pnt->color);
			lst_point = lst_point->next;
		}
		y_index += img->nums->div;
		grid = grid->next;
	}
}
