/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 11:51:03 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 10:31:10 by ayassin          ###   ########.fr       */
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

void	rotate(int key, t_scn *scn)
{
	mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	scn->img->img_ptr = mlx_new_image(scn->mlx_ptr, scn->img->width,
			scn->img->hight);
	scn->img->addr = mlx_get_data_addr(scn->img->img_ptr,
			&(scn->img->bits_per_pixel),
			&(scn->img->line_length), &(scn->img->endian));
	if (key == 13)
		scn->nums->beta -= (M_PI_2 / 9.0);
	else if (key == 1)
		scn->nums->beta += M_PI_2 / 9.0;
	else if (key == 0)
		scn->nums->gamma -= M_PI_2 / 9.0;
	else if (key == 2)
		scn->nums->gamma += M_PI_2 / 9.0;
	else if (key == 14)
		scn->nums->alpha -= M_PI_2 / 9.0;
	else if (key == 12)
		scn->nums->alpha += M_PI_2 / 9.0;
	//printf("gamma is %.20f,  beta is %.20f", scn->nums->gamma*180/M_PI, scn->nums->beta*180/M_PI);
	setup_nums(scn->nums, scn->grid, scn->img);
	draw_points(scn->grid, scn->img);
	draw_line(scn->grid, scn->img);
	mlx_clear_window(scn->mlx_ptr, scn->win_ptr);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr, scn->img->img_ptr,
		scn->img->x_pos, scn->img->y_pos);
}

static void	zoom(int key, t_scn *scn)
{
	int	offset;

	offset = (key == 69) * 2 - 1;
	scn->img->zoom += (key == 69) * 2 - 1;
	scn->img->width = scn->img->b_width * scn->img->zoom / 10;
	scn->img->hight = scn->img->b_hight * scn->img->zoom / 10;
	scn->img->x_pos = scn->img->x_pos - 0.1 * offset / 2.0 * scn->img->b_width;
	scn->img->y_pos = scn->img->y_pos - 0.1 * offset / 2.0 * scn->img->b_hight;
	mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	scn->img->img_ptr = mlx_new_image(scn->mlx_ptr, scn->img->width,
			scn->img->hight);
	scn->img->addr
		= mlx_get_data_addr(scn->img->img_ptr, &(scn->img->bits_per_pixel),
			&(scn->img->line_length), &(scn->img->endian));
	setup_nums(scn->nums, scn->grid, scn->img);
	draw_points(scn->grid, scn->img);
	draw_line(scn->grid, scn->img);
	mlx_clear_window(scn->mlx_ptr, scn->win_ptr);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr, scn->img->img_ptr,
		scn->img->x_pos, scn->img->y_pos);
}

int	key_hook(int key, t_scn *scn)
{
	if (key >= 123 && key <= 126)
		trans(key, scn);
	else if ((key >= 0 && key <= 3) || (key >= 12 && key <= 14))
		rotate(key, scn);
	else if (key == 69 || key == 78)
		zoom(key, scn);
	else if (key == 53)
		x_press(scn);
	else if (key == 47)
		nxt_step(scn);
	else if (key == 43)
		mlx_loop_hook(scn->mlx_ptr, nxt_step, scn);
	printf(" The key num is %d\n", key);
	return (0);
}
