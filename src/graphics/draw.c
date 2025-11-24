/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:50 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/24 15:45:48 by fsaffiri         ###   ########.fr       */
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
		*(unsigned int*)dst = color;
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

/********************************** Examples **********************************/

// Example usage of shading with squares code
void	draw_with_shading(t_data *data)
{
	int	original_color = 0x00FF0000; // Bright red
	int	shaded_color;
	
	// No shading (full brightness)
	shaded_color = add_shade(0.0, original_color);
	draw_square(data, 10, 10, 50, shaded_color);
	
	// Quarter shading
	shaded_color = add_shade(0.25, original_color);
	draw_square(data, 70, 10, 50, shaded_color);
	
	// Half shading
	shaded_color = add_shade(0.5, original_color);
	draw_square(data, 130, 10, 50, shaded_color);

	// Three quarter shading
	shaded_color = add_shade(0.75, original_color);
	draw_square(data, 190, 10, 50, shaded_color);
}

void	draw_torch(t_data *img, int x, int y, int flame_color)
{
	// Draw flame (filled circle)
	draw_circle(img, x, y, 80, flame_color);
	
	// Add inner brighter part
	draw_circle(img, x + 10, y - 20, 40, flame_color | 0x44FFFFFF);
	
	// Draw torch handle (rectangle)
	draw_rectangle(img, x - 20, y + 80, 40, 200, 0x8B4513); // Brown
	
	// Add some details to handle
	draw_rectangle(img, x - 10, y + 120, 20, 120, 0xA0522D); // Darker brown
}
