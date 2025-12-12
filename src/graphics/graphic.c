/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:56 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 12:53:37 by fosuna-g         ###   ########.fr       */
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
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_hegith, ts, 0xFF81D8D0);
			else
				draw_square(&game->img, rel_width, rel_hegith, ts, 0xFF084D6E);
			draw_square2(&game->img, rel_width, rel_hegith, ts, 0xFFFFFF);
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
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_height, ts, 0xFF81D8D0);
			else
				draw_square(&game->img, rel_width, rel_height, ts, 0xFF084D6E);
			draw_square2(&game->img, rel_width, rel_height, ts, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_bold_text_menu(t_game *game, int x, int y, int color, char *text)
{
	mlx_string_put(game->mlx, game->win, x, y, color, text);
	mlx_string_put(game->mlx, game->win, x + 1, y, color, text);
	mlx_string_put(game->mlx, game->win, x, y + 1, color, text);
	mlx_string_put(game->mlx, game->win, x + 1, y + 1, color, text);
}

void	print_menu(t_game *game)
{
	int	x;
	int	y;

	clear_screen(game, 0x000000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	x = (WIDTH - game->controls_menu.width) / 2;
	y = (HEIGHT - game->controls_menu.height) / 2;
	mlx_put_image_to_window(game->mlx, game->win,
		game->controls_menu.img, x, y);
	if (game->prev_state == STATE_START)
		draw_bold_text_menu(game, WIDTH / 2 - 75, HEIGHT - 50,
			0xFF0000, "Press TAB to return");
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
		pos_x = game->player.posX * game->map.tile_size + ps;
		pos_y = game->player.posY * game->map.tile_size;
		draw_map1(game, game->map.tile_size, ps);
	}
	else
	{
		ps = (HEIGHT / 2) - (game->map.tile_size * game->map.height / 2);
		pos_x = game->player.posX * game->map.tile_size;
		pos_y = game->player.posY * game->map.tile_size + ps;
		draw_map2(game, game->map.tile_size, ps);
	}
	ps = (int)game->map.tile_size * 0.25;
	draw_square(&game->img, (pos_x - ps / 2), (pos_y - ps / 2), ps, 0x00FF00);
}

void	draw_mini_map(t_game *game, double stepX, double stepY)
{
	double	x;
	double	y;
	double	start_x;
	double	start_y;

	start_x = WIDTH * 0.05;
	x = game->player.posX - 5;
	while (x <= game->player.posX + 5)
	{
		y = game->player.posY - 5;
		start_y = HEIGHT * 0.75;
		while (y <= game->player.posY + 5)
		{
			if (y >= 0 && x >= 0 && x < game->map.width && y < game->map.height
				&& game->map.grid[(int)y][(int)x] > '0'
				&& game->map.grid[(int)y][(int)x] <= '9')
				draw_rectangle(&game->img, start_x, start_y, stepX, stepY, 0xFF084D6E);
			start_y += stepY;
			y++;
		}
		start_x += stepX;
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
	draw_rectangle(&game->img, start_x, start_y, width, heigth, 0x000C0C0C);
	draw_mini_map(game, width / 11, heigth / 11);
	start_x = width / 2 + start_x - width * 0.03;
	start_y = heigth / 2 + start_y - heigth * 0.03;
	draw_rectangle(&game->img, start_x, start_y, width * 0.03,
		heigth * 0.03, 0x00ff00);
}
