/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 18:21:40 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/05 16:13:36 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_player_pos(char c, t_game *game, int col, int row)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.initial_dir = c;
		game->player.posX = col + 0.5;
		game->player.posY = row + 0.5;
		return (1);
	}
	else if (c != '0' && c != '1' && c != ' ')
		ft_error(8, game);
	return (0);
}

static void	ft_scan_row(t_game *game, int row_index, int *player_count)
{
	int	col_index;
	int	row_length;

	row_length = ft_strlen(game->map.grid[row_index]);
	if (row_length > game->map.width)
		game->map.width = row_length;
	col_index = 0;
	while (game->map.grid[row_index][col_index])
	{
		*player_count += ft_check_player_pos(game->map.grid
			[row_index][col_index], game, col_index, row_index);
		col_index++;
	}
}

void	ft_scan_and_validate(t_game *game)
{
	int	player_count;
	int	row_index;

	player_count = 0;
	row_index = 0;
	while (game->map.grid[row_index])
	{
		ft_scan_row(game, row_index, &player_count);
		row_index++;
	}
	game->map.height = row_index;
	if (player_count != 1)
		ft_error(9, game);
}

static void	ft_alloc_new_row(t_game *game, char **new_grid, int row)
{
	new_grid[row] = malloc(sizeof(char) * (game->map.width + 1));
	if (!new_grid[row])
	{
		ft_free_split(new_grid);
		ft_error(10, game);
	}
}

static void	ft_fill_row(t_game *game, char **new_grid, int row)
{
	int	col;
	int	original_len;

	original_len = ft_strlen(game->map.grid[row]);
	col = 0;
	while (col < game->map.width)
	{
		if (col < original_len)
			new_grid[row][col] = game->map.grid[row][col];
		else
			new_grid[row][col] = '2';
		col++;
	}
	new_grid[row][col] = '\0';
}

void	ft_rectify_map(t_game *game)
{
	char	**new_grid;
	int		r;

	new_grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!new_grid)
		ft_error(10, game);
	r = 0;
	while (r < game->map.height)
	{
		ft_alloc_new_row(game, new_grid, r);
		ft_fill_row(game, new_grid, r);
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
