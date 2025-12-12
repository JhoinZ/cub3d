/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:10:36 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 18:37:13 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *img, t_text_pos pos, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, pos.x + j, pos.y + i, pos.color);
			j++;
		}
		i++;
	}
}

void	draw_square2(t_data *img, t_text_pos pos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(img, pos.x + i, pos.y, pos.color);
		my_mlx_pixel_put(img, pos.x, pos.y + i, pos.color);
		my_mlx_pixel_put(img, pos.x + size, pos.y + i, pos.color);
		my_mlx_pixel_put(img, pos.x + i, pos.y + size, pos.color);
		i++;
	}
}

/*
** Draws a filled rectangle
** @param img: Pointer to image data  
** @param pos: Position and color (x, y, color)
** @param width: Width of rectangle
** @param height: Height of rectangle
*/
void	draw_rectangle(t_data *img, t_text_pos pos, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(img, pos.x + x, pos.y + y, pos.color);
			x++;
		}
		y++;
	}
}
