/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:08:28 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/05 20:38:56 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


double	calculate_distance_factor(double distance)
{
	double	factor;
	
	// 1. Linear
	factor = distance / 10.0;
	
	// Clamp to [0.0, 1.0]
	if (factor < 0.0)
		factor = 0.0;
	if (factor > 1.0)
		factor = 1.0;
	
	return (factor);
}
int	get_wall_c(int side, double stepX, double stepY)
{
	int	index;

	if (side == 0)
	{
		if (stepX > 0)
			index = 3;
		else
			index = 2;
	}
	else
	{
		if (stepY > 0)
			index = 1;
		else
			index = 0;
	}
	return (index);
}

int	get_pixel_color(t_data *texture, int x, int y)
{
	char	*dst;
	
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return (*(int*)dst);
}

void	calc_texture_data(t_game *game, t_vertical *v, t_ray_result ray)
{
	t_data	*texture;
	double	wall_x;
	int		tex_width;

	texture = &game->texture[v->index];
	tex_width = texture->width;
	
	if (ray.side == 0)
	{
		// For vertical hits (east/west walls) - use the exact Y hit position
		wall_x = ray.hit_y;
	}
	else
	{
		// For horizontal hits (north/south walls) - use the exact X hit position  
		wall_x = ray.hit_x;
	}
	
	wall_x /= game->map.tile_size;  // Convert to tile units
	wall_x -= floor(wall_x);        // Get fractional part within ti
	
	// Calculate texture x coordinate
	v->tex_x = (int)(wall_x * (double)tex_width);
	
	// Adjust texture x for different sides
	if (ray.side == 0 && ray.dirX > 0)
		v->tex_x = tex_width - v->tex_x - 1;
	if (ray.side == 1 && ray.dirY < 0)
		v->tex_x = tex_width - v->tex_x - 1;
}

void	draw_wall_column(t_vertical *v, t_game *game, t_ray_result ray)
{
	t_data	*texture;
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
	double	distance_factor;

	texture = &game->texture[v->index];
	
	// Calculate how much to increase texture coordinate per screen pixel
	step = (double)texture->height / (v->y_end - v->y_start);
	tex_pos = 0;
	distance_factor = calculate_distance_factor(ray.distance);
	
	y = v->y_start;
	while (y < v->y_end)
	{
		// Calculate texture y coordinate
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		
		// Get color from texture
		color = get_pixel_color(texture, v->tex_x, tex_y);
		
		// Apply distance-based shading
		color = add_shade(distance_factor, color);
		
		// Additional shading based on wall orientation (optional)
		if (ray.side == 1) // North/South walls
			color = add_shade(0.1, color); // Slightly darker
		
		// Put pixel on screen
		my_mlx_pixel_put(&game->img, v->x, y, color);
		y++;
	}
}

void	draw_vertical(t_game *game, t_vertical *v, t_ray_result ray)
{
	int	x;
	int	color;

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
	color = create_trgb(255, game->map.ceiling_color.r, game->map.ceiling_color.g, game->map.ceiling_color.b);
	draw_vertical_line(game, v->x, 0, v->y_start - 1, color);
	draw_vertical_line(game, v->x, v->y_end - 3, HEIGHT - 1, create_trgb(255, game->map.floor_color.r, game->map.floor_color.g, game->map.floor_color.b));
}
