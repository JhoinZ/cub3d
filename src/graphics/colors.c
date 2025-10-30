/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:45 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/30 12:25:55 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"

/*
* Creates a color value from transparency and RGB components
*
* @param t: Transparency value (0 = fully transparent, 255 = fully opaque)
* @param r: Red component (0-255)
* @param g: Green component (0-255)
* @param b: Blue component (0-255)
* @return Color in 0xAARRGGBB format
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
/**
 * @return 1 or 0 if the color has brightness
 */
int	is_light(int color)
{
	int		r;
	int		g;
	int		b;
	double	luminance;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255.0;
	return (luminance > 0.7);
}

int choose_color(int side)
{
    if (side == 0) 
        return 0x00FF00 / 2; // Red for x-side (vertical walls)
    else 
        return 0x00FF00; // Green for y-side (horizontal walls)
}

/*
* Adds shading to a color based on distance factor.
*
* Assumes opaque colors (alpha = 0xFF)
* @param distance: 0.0 (no shade) to 1.0 (completely dark)
* @param color: Original color in 0xAARRGGBB format
* @return Shaded color
*/
int	add_shade(double distance, int color)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	if (distance < 0.0)
		distance = 0.0;
	if (distance > 1.0)
		distance = 1.0;
	if (is_light(color))
		return (color);
	factor = 1.0 - distance;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return (0xFF << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}
