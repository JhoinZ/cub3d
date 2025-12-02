/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:56 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/02 17:31:43 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_multiple_rays(t_game *game, int num_rays)
{
	double	half_fov = 0.66 / 2;
	double	center_angle = atan2(-game->player.dirY, game->player.dirX);
	double	left_angle = center_angle - half_fov;
	double	angle_step = 2 * half_fov / (num_rays - 1);
	int i = 0;
	while (i < num_rays)
	{
		double ray_angle = left_angle + i * angle_step;
		double ray_dirX = cos(ray_angle);
		double ray_dirY = -sin(ray_angle);
		draw_ray(game, ray_dirX, ray_dirY, 0x00FF00);
		i++;
	}
}

void	draw_map1(t_game *game, int rel_width, int rel_begin)
{
	int i;
	int	j;
	int	rel_hegith;
	
	i = 0;
	rel_hegith = (HEIGHT / game->map.height);
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size + rel_begin;
			rel_hegith = j * game->map.tile_size;
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_map2(t_game *game, int rel_height, int rel_begin)
{
	int i;
	int	j;
	int	rel_width;
	
	i = 0;
	rel_width = (WIDTH / game->map.width);
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size;
			rel_height = j * game->map.tile_size + rel_begin;
			if (game->map.grid[j][i] > '0' && game->map.grid[j][i] <= '9')
				draw_square(&game->img, rel_width, rel_height, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_height, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_height, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

static void	draw_bold_text_menu(t_game *game, int x, int y, int color, char *text)
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
	mlx_put_image_to_window(game->mlx, game->win, game->controls_menu.img, x, y);
	if (game->prev_state == STATE_START)
		draw_bold_text_menu(game, WIDTH / 2 - 75, HEIGHT - 50,
			0xFF0000, "Press TAB to return");
}

void	print_map(t_game *game)
{
	int	posX;
	int	posY;
	int	pS;

	clear_screen(game, 0x000C0C0C);
	if (WIDTH / game->map.tile_size > (game->map.width + 1))
	{
		pS = (WIDTH / 2) - (game->map.tile_size * game->map.width / 2);
		posX = game->player.posX * game->map.tile_size + pS;
		posY = game->player.posY * game->map.tile_size;
		draw_map1(game, game->map.tile_size, pS);
	}
	else
	{
		pS = (HEIGHT / 2) - (game->map.tile_size * game->map.height / 2);
		posX = game->player.posX * game->map.tile_size;
		posY = game->player.posY * game->map.tile_size + pS;
		draw_map2(game, game->map.tile_size, pS);
	}
	pS = (int)game->map.tile_size * 0.25;
	draw_square(&game->img, (posX - pS / 2), (posY - pS / 2), pS, 0x00FF00);
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
				&& game->map.grid[(int)y][(int)x] > '0' && game->map.grid[(int)y][(int)x] <= '9')
			{
				draw_rectangle(&game->img, start_x, start_y, stepX, stepY, 0xFF084D6E);
			}
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
	int width;
	int	start_y;
	int heigth;

	start_x = WIDTH * 0.05;
	width = WIDTH * 0.2 - start_x;
	start_y = HEIGHT * 0.75;
	heigth = HEIGHT * 0.95 - start_y;
	draw_rectangle(&game->img, start_x, start_y, width, heigth, 0x000C0C0C);
	draw_mini_map(game, width / 11, heigth / 11);
	start_x = width / 2 + start_x - width * 0.03;
	start_y = heigth / 2 + start_y - heigth * 0.03;
	draw_rectangle(&game->img, start_x, start_y, width * 0.03, heigth * 0.03, 0x00ff00);
}
