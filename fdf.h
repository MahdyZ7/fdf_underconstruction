/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:20:25 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/29 12:36:37 by ayassin          ###   ########.fr       */
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

# define BASE_COLOR 0x8000ff //0xb0b000
# define ALPHA 0*M_PI_4
# define BETA 0*M_PI_4
# define GAMMA 0*M_PI_4
# define STABILITY 0.5
# define CNT content


typedef struct s_nums
{
	int		width;
	int		hight;
	int		div;
	int		x_trans;
	int		y_trans;
	float	alpha;
	float	beta;
	float	gamma;
	float	cos_a;
	float	sin_a;
	float	cos_b;
	float	sin_b;
	float	cos_g;
	float	sin_g;
}				t_nums;

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
	t_nums	*nums;
}				t_img;

typedef struct s_scn
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_nums	*nums;
	t_list	*grid;
	float	**nxt;		// remeber to insilize as null in setup
	float	**now;		// remember to inislize as null in setup
}				t_scn;

typedef struct s_pnt
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_pnt;

void	pixel_put(t_img *data, int x, int y, int color);
void	setup_nums(t_nums *nums, t_list *grid, t_img *img);

char	*get_next_line(int fd);
char	*get_next_line_loop(char **buff, int readsize, int fd);

t_list	*get_grid(char *file_name);

int		key_hook(int key, t_scn *scn);
void	rotate(int key, t_scn *scn);

void	draw_points(t_list *grid, t_img *img);
void	draw_line(t_list *line, t_img *img);

void	clear_grid(t_list *grid);
int		x_press(t_scn *scn);
void	clear_spc(float ***grid, int hight);

// real bonus
void	int_spc1(t_scn *scn, int width, int hight);
void	int_spc2(t_scn *scn, int width, int hight);
void	setup_spc(t_scn *scn);

int		nxt_step(t_scn *scn);
void	update_grid(t_scn *scn);
void	swap_grids(t_scn *scn);
void	comp_nxt(t_scn *scn, int width, int hight);

// dummy functions;
void	put_ellipse(t_img *img, int width, int hight);
void	put_serpenski(t_img *img, int width, int hight);
void	put_ellipse2(t_img *img, int x, int y);
void	put_border(t_img *img);
void	print_grid(t_list *grid);
void	print_spc(float ***grid, int width, int hight);
int		main2(void);
#endif