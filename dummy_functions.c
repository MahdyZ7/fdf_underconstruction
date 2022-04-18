/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:00:59 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 09:29:46 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_ellipse(t_img *img, int width, int hight)
{
	double	i;
	double	j;
	int		color;

	color = (255 << 16) + (127 << 8) + (0);
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < hight)
		{
			if (pow((i - width / 2.0), 2) / pow(width / 4.0, 2) + pow((j - hight / 2.0), 2) / pow(hight / 4.0, 2) <= 1.0)
			// if (pow((i - width / 2), 2) + pow((j - hight / 2), 2) <= pow(((width+ hight) / 8), 2))
				pixel_put(img, i , j, color);
			++j;
		}
		++i;
	}
}

void	put_serpenski(t_img *img, int width, int hight)
{
	int		i;
	int		j;
	char	*line;
	char	*temp;
	int		color;

	color = 0xff8000;
	line = (char *)malloc(sizeof(*line) * width);
	i = 0;
	while (i < width)
		line[i++] = 0;
	line[width / 2] = 1;
	ft_strlen(line);
	j = 0;
	while (j < hight)
	{
		i = 1;
		temp = (char *)malloc(sizeof(temp) * width);
		temp[0] = 0;
		temp [width - 1] = 0;
		while (i < width - 1)
		{
			if (line[i] == 1)
				pixel_put(img, i, j, color);
			temp[i] = line[i - 1] ^ line[i + 1];
			++i;
		}
		free(line);
		line = temp;
		++color;
		if (color >= 16777215)
			color = (255 << 16) + (127 << 8) + (0);
		++j;
	}
	free(line);
}

void	put_ellipse2(t_img *img, int x, int y)
{
	double	i;
	double	j;
	int		color;
	int		raduis;

	raduis = 4;
	color = (255 << 16) + (127 << 8) + (0);
	i = x - raduis;
	while (i < img->width && i <= x + raduis)
	{
		j = y - raduis;
		while (j < img->hight && j <+ y + raduis)
		{
			if (pow((i - x), 2) + pow((j - y), 2) <= pow(raduis, 2))
				pixel_put(img, i , j, color);
			++j;
		}
		++i;
	}
}

void	put_border(t_img *img)
{
	double	i;
	double	j;
	int		color;

	color = (30 << 16) + (180 << 8) + (255);
	i = 0;
	j = 0;
	while (i < img->width)
	{
		pixel_put(img, i , 0, color);
		pixel_put(img, i , (img->hight) - 1, color);
		i++;
	}
	while (j < img->hight)
	{
		pixel_put(img, 0, j, color);
		pixel_put(img, (img->width) - 1, j, color);
		j++;
	}
}

void	print_grid(t_list *grid)
{
	t_list	*line;
	t_list	*tempg;
	t_list	*templ;

	tempg = grid;
	printf(" the grid is of size %d across * %d down\n",
		ft_lstsize(grid->content), ft_lstsize(grid));
	while (grid)
	{
		line = grid->content;
		templ = line;
		while (line)
		{
			// printf("%d,%x ", ((t_point *)(line->content))->z,
			// 	((t_point *)(line->content))->color);
			printf("%d,%d ", ((t_point *)(line->content))->x_index,
				((t_point *)(line->content))->y_index);
			line = line->next;
		}
		ft_lstclear(&templ, free);
		printf("\n");
		grid = grid->next;
	}
	//ft_lstclear(&tempg, do_nothing);
	while (tempg != 0)
	{
		templ = tempg -> next;
		free(tempg);
		tempg = templ;
	}
}

int	main2(void)
{
	t_scn	scn;
	t_img	img;
	int		width;
	int		hight;

	width = 2000;
	hight = 1000;
	scn.img = &img;
	scn.mlx_ptr = mlx_init();
	scn.win_ptr = mlx_new_window(scn.mlx_ptr, width, hight, "Trial");

	scn.img->width = width / 2;
	scn.img->hight = hight / 2;	
	scn.img->img_ptr = mlx_new_image(scn.mlx_ptr, scn.img->width, scn.img->hight);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	
	put_serpenski(&img, width/2, hight/2);
	img.x_pos = width / 4;
	img.y_pos = hight / 4;
	mlx_put_image_to_window(scn.mlx_ptr, scn.win_ptr, img.img_ptr, width/4, hight/4);
	mlx_string_put(scn.mlx_ptr, scn.win_ptr, 0, 0, 0xff8000, "MY NAME IS");
	//mlx_destroy_image(scn.mlx_ptr, img.img_ptr);
	mlx_key_hook(scn.win_ptr, key_hook, &scn);
	mlx_loop(scn.mlx_ptr);
	return (0);
}


void	dummy_draw_lines_helper(t_point *point0, t_point *point1, t_img *img)
{
	double	dxy[2];
	double	sxy[2];
	double	error[2];
	int		xy[2];
// plotLine(x0, y0, x1, y1)
//     dx = abs(x1 - x0)
	dxy[0] = fabs((point1->x) * 1.0 - (point0->x) * 1.0);
//     sx = x0 < x1 ? 1 : -1
	sxy[0] = ((point0->x) < (point1->x)) * 2.0 - 1.0;
//     dy = -abs(y1 - y0)
	dxy[1] = -fabs((point1->y) * 1.0 - (point0->y) * 1.0);
//     sy = y0 < y1 ? 1 : -1
	sxy[1] = ((point0->y) < (point1->y)) * 2.0 - 1.0;
//     error = dx + dy
	error[0] = dxy[0] + dxy[1];
	xy[0] = point0->x;
	xy[1] = point0->y;
	while (1)
	{
//         plot(x0, y0)
		pixel_put(img, xy[0], xy[1], point0->color);
//         if x0 == x1 && y0 == y1 break
		if (xy[0] == point1->x && xy[1] == point1->y)
			break ;
//         e2 = 2 * error
		error[1] = 2 * error[0];
//         if e2 >= dy
//             if x0 == x1 break
//             error = error + dy
//             x0 = x0 + sx
//         end if
		if (error[1] >= dxy[1])
		{
			if(xy[0] == point1->x)
				break ;
			error[0] += dxy[1];
			xy[0] += sxy[0];
		}
//         if e2 <= dx
//             if y0 == y1 break
//             error = error + dx
//             y0 = y0 + sy
//         end if
		if (error[1] <= dxy[0])
		{
			if(xy[1] == point1->y)
				break ;
			error[0] += dxy[0];
			xy[1] += sxy[1];
		}
	}
}