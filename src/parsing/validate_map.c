/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:33:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 12:01:47 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_flood_fill(char **map, int x, int y, t_tools *tools)
{
	char	curr_char;

	curr_char = map[y][x];
	if (x < 0 || x >= tools->map_width || y < 0 || y >= tools->map_height)
		ft_error(11, tools);
	if (curr_char == '1' || curr_char == '2' || curr_char == 'V')
		return ;
	if (x == 0 || x == tools->map_width - 1
		|| y == 0 || y == tools->map_height - 1)
		ft_error(11, tools);
	map[y][x] = 'V';
	ft_flood_fill(map, x + 1, y, tools);
	ft_flood_fill(map, x - 1, y, tools);
	ft_flood_fill(map, x, y + 1, tools);
	ft_flood_fill(map, x, y - 1, tools);
}

char	**ft_copy_map_grid(char **map, t_tools *tools)
{
	int		r;
	char	**new_grid;

	new_grid = malloc(sizeof(char *) * (tools->map_height + 1));
	if (!new_grid)
		ft_error(10, tools);
	r = 0;
	while (r < tools->map_height)
	{
		new_grid[r] = ft_strdup(map[r]);
		if (!new_grid[r])
			ft_error(10, tools);
		r++;
	}
	new_grid[r] = NULL;
	return (new_grid);
}

void	ft_validate_map(t_tools *tools)
{
	char	**tmp_map;

	tmp_map = ft_copy_map_grid(tools->map_grid, tools);
	ft_flood_fill(tmp_map, (int)tools->player.pos_x,
		(int)tools->player.pos_y, tools);
	ft_free_split(tmp_map);
}
