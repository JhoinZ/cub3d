/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:42 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/06 17:03:35 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	animation_loop(void *param)
{
	static long int	last_time = 0;
	static float	total_time = 0.0f;
	long int		delta_time;
	t_game			*game;
	
	game = (t_game *)param;
	if (last_time == 0)
		last_time = get_time();
	delta_time = get_diff_time(last_time);
	last_time = get_time();
	total_time += delta_time / 1000.0f;
	// Clear screen
	clear_screen(game, 0x00224466);
	animate_torch_smooth(&game->img, 200, 200, total_time);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

/************************************* Examples *************************************/

void	animate_torch_smooth(t_data *img, int x, int y, float time)
{
	// Use sine wave for smooth pulsing - cycles every 2π seconds
	float intensity = (sinf(time * 3.0f) + 1.0f) / 2.0f;  // 0.0 to 1.0
	
	// Blend between dark and bright orange based on time
	int base_color = 0xFF3300;    // Dark red-orange
	int bright_color = 0xFFFF00;  // Bright yellow
	
	int r = ((base_color >> 16) & 0xFF) * (1.0f - intensity) + 
			((bright_color >> 16) & 0xFF) * intensity;
	int g = ((base_color >> 8) & 0xFF) * (1.0f - intensity) + 
			((bright_color >> 8) & 0xFF) * intensity;
	int b = (base_color & 0xFF) * (1.0f - intensity) + 
			(bright_color & 0xFF) * intensity;
	
	int torch_color = (0xFF << 24) | ((int)r << 16) | ((int)g << 8) | (int)b;
	draw_torch(img, x, y, torch_color);
}
