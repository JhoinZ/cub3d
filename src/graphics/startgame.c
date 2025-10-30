/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startgame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:43:07 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 11:41:31 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_setup_mlx_and_game(t_tools *tools)
{
	tools->mlx_ptr = mlx_init();
	if (tools->mlx_ptr == NULL)
		ft_error(4, tools);
	tools->win_ptr = mlx_new_window(tools->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (tools->win_ptr == NULL)
		ft_error(4, tools);
	tools->img_buffer.img_ptr = mlx_new_image(tools->mlx_ptr, WIDTH, HEIGHT);
	if (tools->img_buffer.img_ptr == NULL)
		ft_error(4, tools);
	tools->img_buffer.addr = mlx_get_data_addr(
		tools->img_buffer.img_ptr,
		&tools->img_buffer.bpp,
		&tools->img_buffer.line_length,
		&tools->img_buffer.endian
	);
	ft_load_mlx_textures(tools);
	ft_set_hooks(tools);
	mlx_loop(tools->mlx_ptr);
}

void	ft_init_player_vectors(t_tools *tools)
{
	char	dir;

	dir = tools->player.initial_dir;
	if (dir == 'N')
	{
		tools->player.dir_y = -1.0;
		tools->player.plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		tools->player.dir_y = 1.0;
		tools->player.plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		tools->player.dir_x = 1.0;
		tools->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		tools->player.dir_x = -1.0;
		tools->player.plane_y = -0.66;
	}
}
