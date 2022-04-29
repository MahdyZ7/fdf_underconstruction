/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:19:33 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 10:54:27 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || y >= data->hight || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	setup_nums(t_nums *nums, t_list *grid, t_img *img)
{
	(void) grid;
	nums->div = (img->width) / 2 / nums->width;
	if (nums->div > (img->hight) / 2 / nums->hight)
		nums->div = (img->hight) / 2 / nums->hight;
	if (nums->div == 0)
		nums->div = 1;
	nums->cos_a = cosf(nums->alpha);
	nums->sin_a = sinf(nums->alpha);
	nums->cos_b = cosf(nums->beta);
	nums->sin_b = sinf(nums->beta);
	nums->cos_g = cosf(nums->gamma);
	nums->sin_g = sinf(nums->gamma);
}

void	setup_img(t_img *img, t_scn *scn, int width, int hight)
{
	img->width = width;
	img->hight = hight;
	img->b_width = width;
	img->b_hight = hight;
	img->zoom = 10;
	img->img_ptr = mlx_new_image(scn->mlx_ptr, img->width, img->hight);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->x_pos = 0;
	img->y_pos = 0;
	scn->nums->width = ft_lstsize(scn->grid->content);
	scn->nums->hight = ft_lstsize(scn->grid);
	scn->nums->beta = BETA;
	scn->nums->gamma = GAMMA;
	scn->nums->alpha = ALPHA;
	scn->nums->x_trans = (img->width) / 2;
	scn->nums->y_trans = (img->hight) / 2;
}

int	main_setup(t_scn *scn, char *map)
{
	int		width;
	int		hight;

	width = 2000;
	hight = 1000;
	scn->mlx_ptr = mlx_init();
	if (ft_strchr(map, '/'))
		map = ft_strrchr(map, '/') + 1;
	scn->win_ptr = mlx_new_window(scn->mlx_ptr, width, hight, map);
	setup_img(scn->img, scn, width, hight);
	setup_nums(scn->nums, scn->grid, scn->img);
	// scn->now = NULL;
	// scn->nxt = NULL;
	setup_spc(scn);
	draw_points(scn->grid, scn->img);
	draw_line(scn->grid, scn->img);
	mlx_put_image_to_window(scn->mlx_ptr, scn->win_ptr,
		scn->img->img_ptr, scn->img->x_pos, scn->img->y_pos);
	mlx_key_hook(scn->win_ptr, key_hook, scn);
	mlx_hook(scn->win_ptr, 17, 0, x_press, scn);
	mlx_loop(scn->mlx_ptr);
	return (0);
}

int	main(int argv, char **argc)
{
	t_scn	scn;
	t_img	img;
	t_nums	nums;

	if (argv != 2)
		return (0);
	scn.img = &img;
	img.nums = &nums;
	scn.nums = &nums;
	scn.grid = get_grid(argc[1]);
	if (scn.grid)
		main_setup(&scn, argc[1]);
	return (0);
}
