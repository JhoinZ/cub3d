/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:08:28 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/29 13:26:24 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_wall_c(int side, double stepX, double stepY)
{
	int	index;

	if (side == 0)
	{
		if (stepY < 0)
			index = 0;
		else
			index = 1;
	}
	else
	{
		if (stepX < 0)
			index = 3;
		else
			index = 2;
	}
}

void	calc_texture_data(t_game *game, t_vertical *v, t_ray_result ray)
{
	
}


void	draw_vertical(t_game *game, t_vertical *v, t_ray_result ray)
{
	int	x;

	if (ray.side == 0)
	{
		x = ray.hit_x - floor(ray.hit_x / game->map.tile_size) * game->map.tile_size;
		
	}
	else
	{
		x = ray.hit_y - floor(ray.hit_y / game->map.tile_size) * game->map.tile_size;
		
	}
	v->tex_x_normalized = x / game->map.tile_size;
	v->index = get_wall_c(ray.side, ray.stepX, ray.stepY);
	calc_texture_data(game, &v, ray);
	draw_wall_column(); // refill this function
	draw_vertical_line(game, v->x, v->y_start, v->y_end, choose_color(ray.side));
	draw_vertical_line(game, v->x, 0, v->y_start - 1, game->map.ceiling_color);
	draw_vertical_line(game, v->x, v->y_end + 1, HEIGHT - 1, game->map.floor_color);
}
