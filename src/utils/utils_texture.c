/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:15:34 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 19:44:57 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_walls(int *map_x, int *map_y, t_game *game)
{
	if (*map_y >= 0 && *map_y < game->map.height
		&& *map_x >= 0 && *map_x < game->map.width)
	{
		if (game->map.grid[*map_y][*map_x] >= '1' &&
			game->map.grid[*map_y][*map_x] <= '9')
			return (1);
		return (0);
	}
	else
		return (1);
}

double	distance_factor(double distance)
{
	double	factor;

	factor = distance / 10.0;
	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;
	return (factor);
}

int	get_pixel_color(t_data *texture, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(int *) dst);
}

void	print_menu(t_game *game)
{
	int			x;
	int			y;
	t_text_pos	hint;

	clear_screen(game, 0x000000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	x = (WIDTH - game->controls_menu.width) / 2;
	y = (HEIGHT - game->controls_menu.height) / 2;
	mlx_put_image_to_window(game->mlx, game->win,
		game->controls_menu.img, x, y);
	if (game->prev_state == STATE_START)
	{
		hint.x = WIDTH / 2 - 75;
		hint.y = HEIGHT - 50;
		hint.color = 0xFF0000;
		draw_bold_text(game, hint, "Press TAB to return");
	}
}

void	draw_tile(t_game *game, int x, int y, char tile)
{
	t_text_pos	pos;
	int			ts;

	ts = game->map.tile_size;
	if (tile > '0' && tile <= '9')
		pos = (t_text_pos){x, y, 0xFF81D8D0};
	else
		pos = (t_text_pos){x, y, 0xFF084D6E};
	draw_square(&game->img, pos, ts);
	pos.color = 0xFFFFFF;
	draw_square2(&game->img, pos, ts);
}
