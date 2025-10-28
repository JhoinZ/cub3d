/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/28 13:04:34 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_scan_and_validate(t_tools *tools)
{
	char	c;
	int		player_count;
	int		row_index;
	int		col_index;
	int		row_lenght;
	
	player_count = 0;
	row_index = 0;
	row_lenght = 0;
	while (tools->map_grid[row_index])
	{
		row_lenght = ft_strlen(tools->map_grid[row_index]);
		if (row_lenght > tools->map_width)
			tools->map_width = row_lenght;
		col_index = 0;
		while (tools->map_grid[row_index][col_index])
		{
			c = tools->map_grid[row_index][col_index];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				tools->player.initial_dir = c;
				tools->player.pos_x = col_index;
				tools->player.pos_y = row_index;
			}
			else if (c != '0' && c != '1' && c != ' ')
				ft_error(8, tools);
			col_index++;
		}
		row_index++;
	}
	tools->map_height = row_index;
	if (player_count != 1)
		ft_error(9, tools);
}

void	ft_rectify_map(t_tools *tools)
{
	int		original_row;
	char	**new_grid;
	int		r;
	int		c;

	new_grid = malloc(sizeof(char *) * (tools->map_height + 1));
	if (!new_grid)
		ft_error(10, tools);
	r = 0;
	while (r < tools->map_height)
	{
		new_grid[r] = malloc(sizeof(char) * (tools->map_width + 1));
		if (!new_grid[r])
		{
			ft_free_split(new_grid);
			ft_error(10, tools);
		}
		original_row = ft_strlen(tools->map_grid[r]);
		c = 0;
		while (c < tools->map_width)
		{
			if (c < original_row)
				new_grid[r][c] = tools->map_grid[r][c];
			else
				new_grid[r][c] = '2';
			c++;
		}
		new_grid[r][c] = '\0';
		r++;
	}
	new_grid[r] = NULL;
	ft_free_split(tools->map_grid);
	tools->map_grid = new_grid;
}

void	ft_create_map(char *map_buffer, t_tools *tools)
{
	if (!map_buffer)
		ft_error(3, tools);
	tools->map_grid = ft_split(map_buffer, '\n');
	if (!tools->map_grid)
		ft_error(3, tools);
	free(map_buffer);
	ft_scan_and_validate(tools);
	ft_rectify_map(tools);
}