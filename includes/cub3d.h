/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:37 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/27 13:53:53 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.141592653589
# define DEBUG 0

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "key.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_player {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	move_speed;
	double	rot_speed;
} t_player;

typedef struct s_map{
	char	**grid;
	int		width;
	int		height;
	int		tile_size;
	int		floor_color;
	int		ceiling_color;
	char	**textures;
} t_map;

typedef struct s_ray_result
{
/* 	double	dirX;
	double	dirY;
	double	stepX;
	double	stepY;
	double	sidedistX;
	double	sidedistY; */
	//	Aqui hay una separacion
	double	distance;
	double	hit_x;
	double	hit_y;
	int		side;
} t_ray_result;


typedef struct s_game {
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	t_map		map;
	int			frame_count;
	int			minimap_scale;
}	t_game;

/* Hook functions */
int		xclose(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	rot_move(t_player *player, int direction);
void	player_move(t_game *game, int keycode);
int		touch(double px, double py, t_game *game);
double	ray_dist(t_game *game, double dirX, double dirY);

/* Graphic functions */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		add_shade(double distance, int color);
int		create_trgb(int t, int r, int g, int b);
void	draw_torch(t_data *img, int x, int y, int flame_color);
void	draw_with_shading(t_data *data);
void	draw_square(t_data *img, int x, int y, int size, int color);
void	draw_square2(t_data *img, int x, int y, int size, int color);
void	draw_rectangle(t_data *img, int start_x, int start_y, int width, int height, int color);
void	draw_circle(t_data *img, int center_x, int center_y, int radius, int color);
void	draw_ray(t_game *game, double dirX, double dirY, int color);
void	animate_torch_smooth(t_data *img, int x, int y, float time);
int		animation_loop(void *param);
void	clear_screen(t_game *game, int color);

/* Utils */
void    display_error(int n, char *msg);
void	clean_exit(int n, t_game *game, char *msg);
void	free_map(t_map *map);

/* Time functions */
void		wait(long time_to_sleep);
long int	get_time(void);
long int	get_diff_time(long int init_time);

#endif