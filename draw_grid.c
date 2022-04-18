/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:06:31 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 14:23:37 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dl_helper(t_point point0, t_point *point1, t_img *img)
{
	double	dxy[2];
	double	sxy[2];
	double	error[2];

	dxy[0] = fabs((point1->x) * 1.0 - (point0.x) * 1.0);
	sxy[0] = ((point0.x) < (point1->x)) * 2.0 - 1.0;
	dxy[1] = -fabs((point1->y) * 1.0 - (point0.y) * 1.0);
	sxy[1] = ((point0.y) < (point1->y)) * 2.0 - 1.0;
	error[0] = dxy[0] + dxy[1];
	while (1)
	{
		pixel_put(img, point0.x, point0.y, point0.color);
		if (point0.x == point1->x && point0.y == point1->y)
			break ;
		error[1] = 2 * error[0];
		if (error[1] >= dxy[1])
		{
			//if (point0.x == point1->x)
			//	break ;
			error[0] += dxy[1];
			point0.x += sxy[0];
		}
		if (error[1] <= dxy[0])
		{
			//if (point0.y == point1->y)
			//	break ;
			error[0] += dxy[0];
			point0.y += sxy[1];
		}
	}
}

void	draw_line(t_list *line, t_img *img)
{
	t_list	*pt;
	t_list	*nxt_pt;
	t_list	*low_pt;

	while (line)
	{
		pt = (t_list *)(line->content);
		nxt_pt = pt->next;
		if (line->next)
			low_pt = line->next->content;
		else
			low_pt = NULL;
		while (pt)
		{
			if (nxt_pt)
			{
				dl_helper(*(t_point *)(pt->content), nxt_pt->content, img);
				nxt_pt = nxt_pt->next;
			}
			if (low_pt)
			{
				dl_helper(*(t_point *)(pt->content), low_pt->content, img);
				low_pt = low_pt->next;
			}
			pt = pt->next;
		}
		line = line->next;
	}
}

void	draw_points(t_list *grid, t_img *img)
{
	int		x_strpt;
	int		y_strpt;
	int		div;
	t_list	*point;
	int		x_index;
	int		y_index;

	x_strpt = (img->width) / 2;
	y_strpt = (img->hight) / 2;
	div = (img->width) / 2 / ft_lstsize(grid->content);
	if (div > (img->hight) / 2 / ft_lstsize(grid))
		div = (img->hight) / 2 / ft_lstsize(grid);
	y_index = 0  - ft_lstsize(grid) / 2;
	put_border(img);
	while (grid)
	{
		point = grid->content;
		x_index = 0 - ft_lstsize(point) / 2;
		while (point)
		{
		// Normal Grid
			// ((t_point *)(point->content))->x = (x_index * div + x_strpt);
			// ((t_point *)(point->content))->y = y_index * div + y_strpt;
			
			// ((t_point *)(point->content))->x = x_index * div * cosf(img->alpha) + y_index * div * sinf(img->alpha) + x_strpt;
			// ((t_point *)(point->content))->y = y_index * div * cosf(img->alpha) - x_index * div * sinf(img->alpha) + y_strpt;
			//printf("x: %d, y = %d\n", ((t_point *)(point->content))->x, ((t_point *)(point->content))->y);

		// rotate and translate without gamma vodo and with some fliped signs
			// ((t_point *)(point->content))->y = ((y_index * div) * cos(img->gamma)
			// 	- (x_index * div) * sin(img->gamma) * sin(img->beta)
			// 	- ((t_point *)(point->content))->z * sin(img->gamma) * cos(img->beta) * div) + y_strpt;
			// ((t_point *)(point->content))->x = ((x_index * div) * cos(img->beta)
			// 	- ((t_point *)(point->content))->z * sin(img->beta) * div)  + x_strpt;

		// // rotate and translate without gamma vodo and with  other fliped signs
			// ((t_point *)(point->content))->y = ((y_index * div) * cosf(img->gamma)
			// 	- (x_index * div) * sinf(img->gamma) * sinf(img->beta)
			// 	+ ((t_point *)(point->content))->z * sinf(img->gamma) * cosf(img->beta) * div) + y_strpt;
			// ((t_point *)(point->content))->x = ((x_index * div) * cosf(img->beta)
			// 	+ ((t_point *)(point->content))->z * sinf(img->beta) * div)  + x_strpt;

		// rotate and translate one at a time
			((t_point *)(point->content))->x = x_index * div * cosf(img->alpha) + y_index * div * sinf(img->alpha);
			((t_point *)(point->content))->y = y_index * div * cosf(img->alpha) - x_index * div * sinf(img->alpha);
			((t_point *)(point->content))->y = (((t_point *)(point->content))->y * cosf(img->gamma)
				- (((t_point *)(point->content))->x) * sinf(img->gamma) * sinf(img->beta)
				- ((t_point *)(point->content))->z * sinf(img->gamma) * cosf(img->beta) * div) + y_strpt;
			((t_point *)(point->content))->x = ((((t_point *)(point->content))->x) * cosf(img->beta)
				- ((t_point *)(point->content))->z * sinf(img->beta) * div)  + x_strpt;
		
		// // 3 axis rotation
		// 	((t_point *)(point->content))->y = ((y_index * div) * (cosf(img->alpha) * cosf(img->gamma) + sinf(img->alpha) * sinf(img->beta) * sinf(img->gamma))
		// 		+ (x_index * div) * (sinf(img->alpha) * sinf(img->gamma) - cosf(img->alpha) * sinf(img->beta) * sinf(img->gamma))
		// 		- ((t_point *)(point->content))->z * sinf(img->gamma) * cosf(img->beta) * div) + y_strpt;
		// 	((t_point *)(point->content))->x = ((x_index * div) * cosf(img->alpha) * cosf(img->beta)
		// 		- ((t_point *)(point->content))->y * sinf(img->alpha) * cosf(img->beta)
		// 		- ((t_point *)(point->content))->z * sinf(img->beta) * div)  + x_strpt;
				
		// wiki 3 axis rotation
			// ((t_point *)(point->content))->y = ((y_index * div) * (cos(img->alpha) * cos(img->gamma) + sin(img->alpha) * sin(img->beta) * sin(img->gamma))
			// 	+ (x_index * div) * sin(img->alpha) * cos(img->beta)
			// 	+ ((t_point *)(point->content))->z * (sin(img->alpha) * sin(img->beta) * cos(img->gamma) - cos(img->alpha) * sin(img->gamma)) * div) + y_strpt;
			// ((t_point *)(point->content))->x = ((x_index * div) * cos(img->alpha) * cos(img->beta)
			// 	+ (y_index * div) * (cos(img->alpha) * sin(img->beta) * sin(img->gamma) - sin(img->alpha) * cos(img->gamma))
			// 	- ((t_point *)(point->content))->z * (cos(img->alpha) * sin(img->beta) * cos(img->gamma) + sin(img->alpha) * sin(img->gamma)) * div)  + x_strpt;

		// New rotate and translate formula
			// ((t_point *)(point->content))->y = ((y_index * div) * cos(img->gamma)
			// 	- (x_index * div) * sin(img->gamma) * cos(img->beta)
			// 	+ ((t_point *)(point->content))->z * sin(img->gamma) * sin(img->beta) * div) + y_strpt;
			// ((t_point *)(point->content))->x = ((x_index * div) * cos(img->gamma) * cos(img->beta)
			// 	+ ((t_point *)(point->content))->y * sin(img->gamma)
			// 	- ((t_point *)(point->content))->z * sin(img->beta) * cos(img->gamma) * div)  + x_strpt;

			
			//printf("This line %d row %d\n", ((t_point *)(point->content))->y, ((t_point *)(point->content))->x);
			//put_ellipse2(img, ((t_point *)(point->content))->x, ((t_point *)(point->content))->y);
			//pixel_put(img, ((t_point *)(point->content))->x, ((t_point *)(point->content))->y, 0xff8000);
			++x_index;
			point = point->next;
		}
		y_index++;
		grid = grid->next;
	}
}