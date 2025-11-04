/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/11/04 12:41:14 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_scan_and_validate(t_game *game)
{
	char	c;
	int		player_count;
	int		row_index;
	int		col_index;
	int		row_lenght;

	player_count = 0;
	row_index = 0;
	row_lenght = 0;
	while (game->map.grid[row_index])
	{
		row_lenght = ft_strlen(game->map.grid[row_index]);
		if (row_lenght > game->map.width)
			game->map.width = row_lenght;
		col_index = 0;
		while (game->map.grid[row_index][col_index])
		{
			c = game->map.grid[row_index][col_index];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				game->player.initial_dir = c;
				game->player.posX = col_index + 0.5;
				game->player.posY = row_index + 0.5;
			}
			else if (c != '0' && c != '1' && c != ' ')
				ft_error(8, game);
			col_index++;
		}
		row_index++;
	}
	game->map.height = row_index;
	if (player_count != 1)
		ft_error(9, game);
}

void	ft_rectify_map(t_game *game)
{
	int		original_row;
	char	**new_grid;
	int		r;
	int		c;

	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		ft_error(10, game);
	r = 0;
	while (r < game->map.height)
	{
		new_grid[r] = malloc(sizeof(char) * (game->map.width + 1));
		if (!new_grid[r])
		{
			ft_free_split(new_grid);
			ft_error(10, game);
		}
		original_row = ft_strlen(game->map.grid[r]);
		c = 0;
		while (c < game->map.width)
		{
			if (c < original_row)
				new_grid[r][c] = game->map.grid[r][c];
			else
				new_grid[r][c] = '2';
			c++;
		}
		new_grid[r][c] = '\0';
		r++;
	}
	new_grid[r] = NULL;
	ft_free_split(game->map.grid);
	game->map.grid = new_grid;
}

void	ft_create_map(char *map_buffer, t_game *game)
{
	if (!map_buffer)
		ft_error(3, game);
	game->map.grid = ft_split(map_buffer, '\n');
	if (!game->map.grid)
		ft_error(3, game);
	free(map_buffer);
	ft_scan_and_validate(game);
	ft_rectify_map(game);
}
