/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:56 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/28 12:17:49 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	int i;
	int	j;
	int	rel_width = game->map.tile_size;
	int	rel_hegith = (HEIGHT / game->map.height);
	int	rel_begin = (WIDTH / 2) - (rel_width * game->map.width / 2);
	
	i = 0;
	(void)game;
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size + rel_begin;
			rel_hegith = j * game->map.tile_size;
			if (game->map.grid[j][i] > '0')
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

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