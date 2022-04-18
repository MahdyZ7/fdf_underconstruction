/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:51:03 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 15:21:26 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	trans(int key, t_scn *scn)
{
	if (key == 126)
		scn->img->y_pos -= 10;
	else if (key == 125)
		scn->img->y_pos += 10;
	else if (key == 123)
		scn->img->x_pos -= 10;
	else if (key == 124)
		scn->img->x_pos += 10;
	mlx_clear_window(scn->mlx_ptr, scn->win_ptr);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr, scn->img->img_ptr,
		scn->img->x_pos, scn->img->y_pos);
}

static void	rotate(int key, t_scn *scn)
{
	mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	scn->img->img_ptr = mlx_new_image(scn->mlx_ptr, scn->img->width, scn->img->hight);
	scn->img->addr = mlx_get_data_addr(scn->img->img_ptr, &(scn->img->bits_per_pixel),
			&(scn->img->line_length), &(scn->img->endian));
	if (key == 13)
		scn->img->beta -= (M_PI_2 / 9.0);
	else if (key == 1)
		scn->img->beta += M_PI_2 / 9.0;
	else if (key == 0)
		scn->img->gamma -= M_PI_2 / 9.0;
	else if (key == 2)
		scn->img->gamma += M_PI_2 / 9.0;
	else if (key == 14)
		scn->img->alpha -= M_PI_2 / 9.0;
	else if (key == 12)
		scn->img->alpha += M_PI_2 / 9.0;
	printf("gamma is %.20f,  beta is %.20f", scn->img->gamma*180/M_PI, scn->img->beta*180/M_PI);
	draw_points(scn->grid, scn->img);
	draw_line(scn->grid, scn->img);
	mlx_clear_window(scn->mlx_ptr, scn->win_ptr);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr, scn->img->img_ptr,
		scn->img->x_pos, scn->img->y_pos);
}

static void	zoom(int key, t_scn *scn)
{
	mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	if (key == 69)
	{
		scn->img->x_pos = scn->img->x_pos - 0.1 / 2.0 * scn->img->width;
		scn->img->y_pos = scn->img->y_pos - 0.1 / 2.0 * scn->img->hight;
		scn->img->width *= 1.1;
		scn->img->hight *= 1.1;
	}
	else
	{
		scn->img->x_pos = scn->img->x_pos + 0.1 / 2.0  * scn->img->width;
		scn->img->y_pos = scn->img->y_pos + 0.1 / 2.0 * scn->img->hight;
		scn->img->width *= 0.9;
		scn->img->hight *= 0.9;
	}
	scn->img->img_ptr = mlx_new_image(scn->mlx_ptr, scn->img->width, scn->img->hight);
	scn->img->addr = mlx_get_data_addr(scn->img->img_ptr, &(scn->img->bits_per_pixel),
			&(scn->img->line_length), &(scn->img->endian));
	draw_points(scn->grid, scn->img);
	draw_line(scn->grid, scn->img);
	mlx_clear_window(scn->mlx_ptr, scn->win_ptr);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr, scn->img->img_ptr,
		scn->img->x_pos, scn->img->y_pos);
}

int	x_press(t_scn *scn)
{
	clear_grid(scn->grid);
	mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	mlx_destroy_window(scn->mlx_ptr, scn->win_ptr);
	exit(0);
}

int	key_hook(int key, t_scn *scn)
{
	if (key >= 123 && key <= 126)
		trans(key, scn);
	if ((key >= 0 && key <= 3) || (key >= 12 && key <= 14))
		rotate(key, scn);
	if (key == 69 || key == 78)
		zoom(key, scn);
	if (key == 53)
		x_press(scn);
	printf(" The key num is %d\n", key);
	return (0);
}