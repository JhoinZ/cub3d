/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:08:28 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/30 12:37:32 by fosuna-g         ###   ########.fr       */
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
	return (index);
}

void	calc_texture_data(t_game *game, t_vertical *v, t_ray_result ray)
{
	int	height;

	height = (int)(HEIGHT / ray.distance);
	v->tex_x = (int)(v->tex_x_normalized * game->texture[v->index].width);
	v->step = 1.0 * game->texture[v->index].height / height;
	v->tex_pos = (v->y_start - HEIGHT / 2 + height / 2) * v->step;
}

void	draw_wall_column(t_vertical *v, t_game *game, t_ray_result ray)
{
	int	color;
	int	height;

	height = (int)(HEIGHT / ray.distance);
	while (v->y_start < v->y_end)
	{
		v->tex_y = (int)v->tex_pos % game->texture[v->index].height;
		if (v->tex_y < 0)
			v->tex_y += game->texture[v->index].height;
		v->tex_pos += v->step;
		v->pixel_addr = game->texture[v->index].addr
				+ (v->tex_y * game->texture[v->index].line_length
					+ v->tex_x * (game->texture[v->index].bits_per_pixel / 8));
		color = *(unsigned int *)v->pixel_addr;
		if (ray.side == 0 && !is_light(color))
			color = (color >> 1) & 8355711;
		//color = add_shade(height, color);
		my_mlx_pixel_put(&game->img, v->x, v->y_start, color);
		v->y_start++;
	}
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
	calc_texture_data(game, v, ray);
	draw_wall_column(v, game, ray); // refill this function
/* 	draw_vertical_line(game, v->x, v->y_start, v->y_end, choose_color(ray.side));
	draw_vertical_line(game, v->x, 0, v->y_start - 1, game->map.ceiling_color);
	draw_vertical_line(game, v->x, v->y_end + 1, HEIGHT - 1, game->map.floor_color); */
}
