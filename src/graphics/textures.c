/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:08:28 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/11/20 18:13:50 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


double	distance_factor(double distance)
{
	double	factor;

	factor = distance / 10.0;
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
	
/* 	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); */
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
		wall_x = ray.hit_y;
	else
		wall_x = ray.hit_x;
	wall_x -= floor(wall_x);
	v->tex_x = (int)(wall_x * (double)tex_width);
	if (ray.side == 0 && ray.dirX < 0)
		v->tex_x = tex_width - v->tex_x - 1;
	if (ray.side == 1 && ray.dirY > 0)
		v->tex_x = tex_width - v->tex_x - 1;
}

void	draw_wall_column(t_vertical *v, t_game *game, t_ray_result ray)
{
	t_data	*texture;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;


	int actual_start = v->y_start;
	int actual_end = v->y_end;
	if (actual_start < 0) actual_start = 0;
	if (actual_end > HEIGHT) actual_end = HEIGHT;
	texture = &game->texture[v->index];
	step = (double)texture->height / (v->y_end - v->y_start);
	if (v->y_start < 0)
		tex_pos = -v->y_start * step;
	else
		tex_pos = 0;
	while (actual_start < actual_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(texture, v->tex_x, tex_y);
		color = add_shade(distance_factor(ray.distance), color);
		if (ray.side == 1)
			color = add_shade(0.1, color);
		my_mlx_pixel_put(&game->img, v->x, actual_start, color);
		actual_start++;
	}
}

void	draw_vertical(t_game *game, t_vertical *v, t_ray_result ray)
{
	int	r;
	int	g;
	int	b;

	if (ray.distance < 0.1)
		ray.distance = 0.1;
	v->index = get_wall_c(ray.side, ray.stepX, ray.stepY);
	calc_texture_data(game, v, ray);
	draw_wall_column(v, game, ray);
	if (v->y_end - v->y_start < HEIGHT)
	{
		r = game->map.ceiling_color.r;
		g = game->map.ceiling_color.g;
		b = game->map.ceiling_color.b;
		draw_vertical_line(game, v->x, 0, v->y_start - 1, create_trgb(255, r, g, b));
		r = game->map.floor_color.r;
		g = game->map.floor_color.g;
		b = game->map.floor_color.b;
		draw_vertical_line(game, v->x, v->y_end - 3, HEIGHT - 1, create_trgb(255, r, g, b));
	}
}
