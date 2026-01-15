/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:33:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/15 13:08:33 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_flood_fill(char **map, int x, int y, t_game *game)
{
	char	curr_char;

	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (1);
	curr_char = map[y][x];
	if (curr_char == '2')
		return (1);
	if (curr_char == '1' || curr_char == 'V')
		return (0);
	if (x == 0 || x == game->map.width - 1
		|| y == 0 || y == game->map.height - 1)
		return (1);
	map[y][x] = 'V';
	if (ft_flood_fill(map, x + 1, y, game))
		return (1);
	if (ft_flood_fill(map, x - 1, y, game))
		return (1);
	if (ft_flood_fill(map, x, y + 1, game))
		return (1);
	if (ft_flood_fill(map, x, y - 1, game))
		return (1);
	return (0);
}

char	**ft_copy_map_grid(char **map, t_game *game)
{
	int		r;
	char	**new_grid;

	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		ft_error(10, game);
	r = 0;
	while (r < game->map.height)
	{
		new_grid[r] = ft_strdup(map[r]);
		if (!new_grid[r])
			ft_error(10, game);
		r++;
	}
	new_grid[r] = NULL;
	return (new_grid);
}

void	ft_validate_map(t_game *game)
{
	char	**tmp_map;
	int		error;

	tmp_map = ft_copy_map_grid(game->map.grid, game);
	error = ft_flood_fill(tmp_map, (int)game->player.pos_x,
			(int)game->player.pos_y, game);
	ft_free_split(tmp_map);
	if (error)
		ft_error(11, game);
}
