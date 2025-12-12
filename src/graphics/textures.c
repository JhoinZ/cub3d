/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:08:28 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 19:22:30 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_wall_c(int side, double stepX, double stepY)
{
	int	index;

	if (side == 0)
	{
		if (step_x > 0)
			index = 3;
		else
			index = 2;
	}
	else
	{
		if (step_y > 0)
			index = 1;
		else
			index = 0;
	}
	return (index);
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
	if (ray.side == 0 && ray.dir_x < 0)
		v->tex_x = tex_width - v->tex_x - 1;
	if (ray.side == 1 && ray.dir_y > 0)
		v->tex_x = tex_width - v->tex_x - 1;
}

void	wall_loop(t_vertical v, t_game *game, t_ray_result ray)
{
	t_data	*texture;
	int		color;
	int		tex_y;

	texture = &game->texture[v.index];
	while (v.a_start < v.a_end)
	{
		tex_y = (int)v.tex_pos & (texture->height - 1);
		v.tex_pos += v.step;
		color = get_pixel_color(texture, v.tex_x, tex_y);
		color = add_shade(distance_factor(ray.distance), color);
		if (ray.side == 1)
			color = add_shade(0.1, color);
		my_mlx_pixel_put(&game->img, v.x, v.a_start, color);
		v.a_start++;
	}
}

void	draw_wall_column(t_vertical *v, t_game *game, t_ray_result ray)
{
	t_data	*texture;

	v->a_start = v->y_start;
	v->a_end = v->y_end;
	if (v->a_start < 0)
		v->a_start = 0;
	if (v->a_end > HEIGHT)
		v->a_end = HEIGHT;
	texture = &game->texture[v->index];
	v->step = (double)texture->height / (v->y_end - v->y_start);
	if (v->y_start < 0)
		v->tex_pos = -v->y_start * v->step;
	else
		v->tex_pos = 0;
	wall_loop(*v, game, ray);
}

void	draw_vertical(t_game *game, t_vertical *v, t_ray_result ray)
{
	if (ray.distance < 0.1)
		ray.distance = 0.1;
	v->index = get_wall_c(ray.side, ray.step_x, ray.step_y);
	calc_texture_data(game, v, ray);
	draw_wall_column(v, game, ray);
	if (v->y_end - v->y_start < HEIGHT)
	{
		draw_vertical_line(game, (t_text_pos){v->x, 0, game->map.ceiling_color},
			0, v->y_start - 1);
		draw_vertical_line(game, (t_text_pos){v->x, 0, game->map.floor_color},
			v->y_end - 3, HEIGHT - 1);
	}
}
