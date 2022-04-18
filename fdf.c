/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:19:33 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 15:21:10 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || y >= data->hight)
	{
		printf("You messed up\n");
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main3(t_list *grid)
{
	t_scn	scn;
	t_img	img;
	int		width;
	int		hight;

	width = 2000;
	hight = 1000;
	scn.img = &img;
	scn.mlx_ptr = mlx_init();
	scn.win_ptr = mlx_new_window(scn.mlx_ptr, width, hight, "Trial 2");

	img.width = width;
	img.hight = hight;
	img.b_width = width;
	img.b_hight = hight;
	img.zoom = 10;
	img.img_ptr = mlx_new_image(scn.mlx_ptr, scn.img->width, scn.img->hight);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	scn.img->beta = 0; //-M_PI_4;
	scn.img->gamma = 0; //M_PI / 6.0;
	scn.img->alpha = 0;
	draw_points(grid, &img);
	draw_line(grid, &img);
	img.x_pos = 0;
	img.y_pos = 0;
	mlx_put_image_to_window(scn.mlx_ptr, scn.win_ptr, img.img_ptr, img.x_pos, img.y_pos);
	mlx_key_hook(scn.win_ptr, key_hook, &scn);
	mlx_hook(scn.win_ptr, 17, 0, x_press, &scn);
	mlx_loop(scn.mlx_ptr);
	return (0);
}

int	main(int argv, char **argc)
{
	t_list	*grid;

	if (argv != 2)
		return (0);
	grid = get_grid(argc[1]);
	main3(grid);
	return (0);
}
