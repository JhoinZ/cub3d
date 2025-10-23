/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/23 13:09:11 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_data	img;
	
}				t_game;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_game init_game(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
									&game.img.line_length, &game.img.endian);
	
	return (game);
}

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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Adds shading to a color based on distance factor.
**
** Assumes opaque colors (alpha = 0xFF)
** @param distance: 0.0 (no shade) to 1.0 (completely dark)
** @param color: Original color in 0xAARRGGBB format
** @return Shaded color
*/
int	add_shade(double distance, int color)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	if (distance < 0.0) distance = 0.0;
	if (distance > 1.0) distance = 1.0;
	
	factor = 1.0 - distance;
	
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	
	return (0xFF << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int	windows_close(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(game->mlx, game->img.img);
		mlx_destroy_window(game->mlx, game->win);
		mlx_loop_end(game->mlx);
	}
	return (0);
}

int	xclose(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_loop_end(game->mlx);
	return (0);
}

int	know_the_key(int keycode, t_game *game)
{
	(void)game;
	printf("Kecode of the key pressed: %d\n", keycode);
	return (0);
}

// Example usage in your drawing code
void	draw_with_shading(t_data *data)
{
	int	original_color = 0x00FF0000; // Bright red
	int	shaded_color;
	
	// No shading (full brightness)
	shaded_color = add_shade(0.0, original_color);
	draw_square(data, 10, 10, 50, shaded_color);
	
	// Half shading
	shaded_color = add_shade(0.5, original_color);
	draw_square(data, 70, 10, 50, shaded_color);
	
	// Complete shading (black)
	shaded_color = add_shade(1.0, original_color);
	draw_square(data, 130, 10, 50, shaded_color);
	
	// Quarter shading
	shaded_color = add_shade(0.25, original_color);
	draw_square(data, 190, 10, 50, shaded_color);
}

int	main(void)
{
	t_game	game;

	game = init_game();
	
	draw_with_shading(&game.img);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	//mlx_hook(game.win, 2, 1L<<0, windows_close, &game); // this is for keydown
	mlx_key_hook(game.win, windows_close, &game); // this is for keyup
	mlx_loop(game.mlx);
	return (0);
}
