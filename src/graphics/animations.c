/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:42 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 13:08:53 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	animation_loop(void *param)
{
	static long int	last_time;
	static float	total_time;
	long int		delta_time;
	t_game			*game;

	last_time = 0;
	total_time = 0.0f;
	game = (t_game *)param;
	if (last_time == 0)
		last_time = get_time();
	delta_time = get_diff_time(last_time);
	last_time = get_time();
	total_time += delta_time / 1000.0f;
	clear_screen(game, 0x00224466);
	animate_torch_smooth(&game->img, 200, 200, total_time);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
