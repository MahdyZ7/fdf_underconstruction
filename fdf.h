/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:20:25 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 15:19:49 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx_macos/mlx.h"
# include "libft_beta/libft.h"
# include "ft_printf_beta/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> // for printf
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		b_width;
	int		b_hight;
	int		width;
	int		hight;
	int		zoom;
	int		x_pos;
	int		y_pos;
	float	alpha;
	float	beta;
	float	gamma;
}				t_img;

typedef struct s_scn
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_list	*grid;
	//int		*prv_grid;		// remeber to insilize as null in setup
	//int		*now_grid;		// remember to inislize as null in setup
}				t_scn;

typedef struct s_point
{
	int			x_index;
	int			y_index;
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

void	pixel_put(t_img *data, int x, int y, int color);

char	*get_next_line(int fd);
char	*get_next_line_loop(char **buff, int readsize, int fd);

t_list	*get_grid(char *file_name);
void	clear_grid(t_list *grid);

int		key_hook(int key, t_scn *scn);
int		x_press(t_scn *scn);

void	draw_points(t_list *grid, t_img *img);
void	draw_line(t_list *line, t_img *img);

// dummy functions;
void	put_ellipse(t_img *img, int width, int hight);
void	put_serpenski(t_img *img, int width, int hight);
void	put_ellipse2(t_img *img, int x, int y);
void	put_border(t_img *img);
void	print_grid(t_list *grid);
int		main2(void);
#endif