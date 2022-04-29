/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:48:12 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/27 11:56:17 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_grid(t_list *grid)
{
	t_list	*temp;
	t_list	*temp2;

	temp2 = grid;
	while (grid)
	{
		temp = grid->content;
		ft_lstclear(&temp, free);
		temp2 = grid;
		grid = grid->next;
		free(temp2);
	}
}

void	clear_spc(float ***grid, int hight)
{
	int	i;

	i = 0;
	while (i < hight)
		free((*grid)[i++]);
	free(*grid);
	*grid = NULL;
}

int	x_press(t_scn *scn)
{
	int	hight;

	if (!scn)
		exit(0);
	if (scn->grid)
	{
		hight = ft_lstsize(scn->grid);
		if (scn)
			clear_spc(&(scn->now), hight);
		if (scn->nxt)
			clear_spc(&(scn->nxt), hight);
		clear_grid(scn->grid);
	}
	if (scn->img)
	{
		if (scn->img->img_ptr)
			mlx_destroy_image(scn->mlx_ptr, scn->img->img_ptr);
	}
	if (scn->mlx_ptr && scn->win_ptr)
		mlx_destroy_window(scn->mlx_ptr, scn->win_ptr);
	exit(0);
	return (0);
}
