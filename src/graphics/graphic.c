/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:56 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 19:44:48 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map1(t_game *game, int rel_width, int rel_begin)
{
	int	i;
	int	j;
	int	rel_hegith;
	int	ts;

	i = 0;
	rel_hegith = (HEIGHT / game->map.height);
	ts = game->map.tile_size;
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * ts + rel_begin;
			rel_hegith = j * ts;
			draw_tile(game, rel_width, rel_hegith, game->map.grid[j][i]);
			j++;
		}
		i++;
	}
}

void	draw_map2(t_game *game, int rel_height, int rel_begin)
{
	int	i;
	int	j;
	int	rel_width;
	int	ts;

	i = 0;
	rel_width = (WIDTH / game->map.width);
	ts = game->map.tile_size;
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * ts;
			rel_height = j * ts + rel_begin;
			draw_tile(game, rel_width, rel_height, game->map.grid[j][i]);
			j++;
		}
		i++;
	}
}

void	print_map(t_game *game)
{
	int	pos_x;
	int	pos_y;
	int	ps;

	clear_screen(game, 0x000C0C0C);
	if (WIDTH / game->map.tile_size > (game->map.width + 1))
	{
		ps = (WIDTH / 2) - (game->map.tile_size * game->map.width / 2);
		pos_x = game->player.pos_x * game->map.tile_size + ps;
		pos_y = game->player.pos_y * game->map.tile_size;
		draw_map1(game, game->map.tile_size, ps);
	}
	else
	{
		ps = (HEIGHT / 2) - (game->map.tile_size * game->map.height / 2);
		pos_x = game->player.pos_x * game->map.tile_size;
		pos_y = game->player.pos_y * game->map.tile_size + ps;
		draw_map2(game, game->map.tile_size, ps);
	}
	ps = (int)game->map.tile_size * 0.25;
	draw_square(&game->img,
		(t_text_pos){(pos_x - ps / 2), (pos_y - ps / 2), 0x00FF00}, ps);
}

void	draw_mini_map(t_game *game, double step_x, double step_y)
{
	double	x;
	double	y;
	double	start_x;
	double	start_y;

	start_x = WIDTH * 0.05;
	x = game->player.pos_x - 5;
	while (x <= game->player.pos_x + 5)
	{
		y = game->player.pos_y - 5;
		start_y = HEIGHT * 0.75;
		while (y <= game->player.pos_y + 5)
		{
			if (y >= 0 && x >= 0 && x < game->map.width && y < game->map.height
				&& game->map.grid[(int)y][(int)x] > '0'
				&& game->map.grid[(int)y][(int)x] <= '9')
				draw_rectangle(&game->img,
					(t_text_pos){start_x, start_y, 0xFF084D6E}, step_x, step_y);
			start_y += step_y;
			y++;
		}
		start_x += step_x;
		x++;
	}
}

void	print_mini_map(t_game *game)
{
	int	start_x;
	int	width;
	int	start_y;
	int	heigth;

	start_x = WIDTH * 0.05;
	width = WIDTH * 0.2 - start_x;
	start_y = HEIGHT * 0.75;
	heigth = HEIGHT * 0.95 - start_y;
	draw_rectangle(&game->img, (t_text_pos){start_x, start_y, 0x000C0C0C},
		width, heigth);
	draw_mini_map(game, width / 11, heigth / 11);
	start_x = width / 2 + start_x - width * 0.03;
	start_y = heigth / 2 + start_y - heigth * 0.03;
	draw_rectangle(&game->img, (t_text_pos){start_x, start_y, 0x00ff00},
		width * 0.03, heigth * 0.03);
}
