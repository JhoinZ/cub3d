/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:50 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 13:20:11 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Faster pixel put function because draws on the image not on the window
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	draw_ray(t_game *game, double dirX, double dirY, int color)
{
	double	ray_x;
	double	ray_y;

	ray_x = game->player.posX;
	ray_y = game->player.posY;
	while (!touch(ray_x, ray_y, game))
	{
		my_mlx_pixel_put(&game->img, ray_x, ray_y, color);
		ray_x += dirX;
		ray_y += dirY;
	}
}

void	draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color)
{
	int	y;

	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	y = start_y;
	while (y <= end_y)
	{
		my_mlx_pixel_put(&game->img, x, y, color);
		y++;
	}
}

void	clear_screen(t_game *game, int color)
{
	draw_rectangle(&game->img, 0, 0, WIDTH, HEIGHT, color);
}
