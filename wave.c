/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:08:23 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/15 12:24:26 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup_spc(t_scn *scn)
{
	int	width;
	int	length;
	int	**now_grid;
	int	**prv_grid;
	int	i;

	width = ft_lstsize(scn->grid->content);
	length = ft_lstsize(scn->grid);
	now_grid = (int **)malloc(sizeof(*now_grid) * length);
	prv_grid = (int **)malloc(sizeof(*prv_grid) * length);
	i = 0;
	while (i < length)
	{
		now_grid[i] = (int *)malloc(sixeof(**now_grid) * width);
		now_grid[i] = (int *)malloc(sixeof(**now_grid) * width);
		++i;
	}
	scn->now_grid = now_grid;
	scn->prv_grid = prv_grid;
}