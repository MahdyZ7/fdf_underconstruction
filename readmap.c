/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:04:42 by ayassin           #+#    #+#             */
/*   Updated: 2022/04/18 09:19:16 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_hexatoi(char *nbr)
{
	int	n;

	n = 0;
	while (*nbr != 'x' && *nbr != 'X')
		nbr++;
	while (*(++nbr))
	{
		if (*nbr >= '0' && *nbr <= '9')
			n = 16 * n + *nbr - '0';
		else if (*nbr >= 'a' && *nbr <= 'f')
			n = 16 * n + *nbr - 'a' + 10;
		else if (*nbr >= 'A' && *nbr <= 'F')
			n = 16 * n + *nbr - 'A' + 10;
	}
	return (n);
}

t_list	*get_points(char *str, int y)
{
	int		i;
	char	**str_sep;
	t_list	*line;
	t_point	*temp;

	i = 0;
	line = NULL;
	str_sep = ft_split(str, ' ');
	free(str);
	while (str_sep[i])
	{
		temp = (t_point *)malloc(sizeof(*temp));
		temp->x_index = i;
		temp->y_index = y;
		temp->z = ft_atoi(str_sep[i]);
		temp->color = 0xffffff;
		if (ft_strchr(str_sep[i], ','))
			temp->color = ft_hexatoi(str_sep[i]);
		ft_lstadd_back(&line, ft_lstnew(temp));
		free(str_sep[i++]);
	}
	free(str_sep);
	return (line);
}

t_list	*get_grid(char *file_name)
{
	t_list	*grid;
	t_list	*temp;
	char	*str;
	int		fd;
	int		y;

	grid = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("The file \"%s\" does not exist\n", file_name);
		exit (-1);
	}
	str = get_next_line(fd);
	y = 0;
	while (str)
	{
		temp = ft_lstnew(get_points(str, y++));
		if (!temp)
		{
			clear_grid(grid);
			ft_printf("Malloc failed\n");
			exit(-1);
		}
		ft_lstadd_back(&grid, temp);
		str = get_next_line(fd);
	}
	close(fd);
	return (grid);
}

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
