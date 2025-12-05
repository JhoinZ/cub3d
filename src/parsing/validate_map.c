/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:33:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/05 16:38:35 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_flood_fill(char **map, int x, int y, t_game *game)
{
	char	curr_char;

	curr_char = map[y][x];
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		ft_error(11, game);
	if (curr_char == '2')
		ft_error(11, game);
	if (curr_char == '1' || curr_char == 'V')
		return ;
	if (x == 0 || x == game->map.width - 1
		|| y == 0 || y == game->map.height - 1)
		ft_error(11, game);
	map[y][x] = 'V';
	ft_flood_fill(map, x + 1, y, game);
	ft_flood_fill(map, x - 1, y, game);
	ft_flood_fill(map, x, y + 1, game);
	ft_flood_fill(map, x, y - 1, game);
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

	tmp_map = ft_copy_map_grid(game->map.grid, game);
	ft_flood_fill(tmp_map, (int)game->player.posX,
		(int)game->player.posY, game);
	ft_free_split(tmp_map);
}
