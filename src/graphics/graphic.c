/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:56 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/25 09:39:04 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_screen(t_game *game, int color)
{
	draw_rectangle(&game->img, 0, 0, WIDTH, HEIGHT, color);
}

// Example usage of shading with squares code
void	draw_with_shading(t_data *data)
{
	int	original_color = 0x00FF0000; // Bright red
	int	shaded_color;
	
	// No shading (full brightness)
	shaded_color = add_shade(0.0, original_color);
	draw_square(data, 10, 10, 50, shaded_color);
	
	// Half shading
	shaded_color = add_shade(0.25, original_color);
	draw_square(data, 70, 10, 50, shaded_color);
	
	// Complete shading (black)
	shaded_color = add_shade(0.5, original_color);
	draw_square(data, 130, 10, 50, shaded_color);
	
	// Quarter shading
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
