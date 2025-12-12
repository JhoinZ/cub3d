/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_figures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 12:10:36 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 13:01:45 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_square2(t_data *img, int x, int y, int size, int color)
{
	int	i;

	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(img, x + i, y, color);
		my_mlx_pixel_put(img, x, y + i, color);
		my_mlx_pixel_put(img, x + size, y + i, color);
		my_mlx_pixel_put(img, x + i, y + size, color);
		i++;
	}
}

/*
** Draws a filled rectangle
** @param img: Pointer to image data  
** @param start_x: Top-left X coordinate
** @param start_y: Top-left Y coordinate
** @param width: Width of rectangle
** @param height: Height of rectangle
** @param color: Color in 0xAARRGGBB format
*/
void	draw_rectangle(t_data *img, int start_x, int start_y, int width, int height, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

/*
** Draws a filled circle using Bresenham's algorithm
** @param img: Pointer to image data
** @param center_x: X coordinate of circle center
** @param center_y: Y coordinate of circle center  
** @param radius: Radius of the circle
** @param color: Color in 0xAARRGGBB format
*/
void	draw_circle(t_data *img, int center_x, int center_y, int radius, int color)
{
	int	x;
	int	y;
	int	delta_x;
	int	delta_y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			delta_x = x;
			delta_y = y;
			if (delta_x * delta_x + delta_y * delta_y <= radius * radius)
			{
				my_mlx_pixel_put(img, center_x + x, center_y + y, color);
			}
			x++;
		}
		y++;
	}
}
