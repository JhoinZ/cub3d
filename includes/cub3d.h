/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:37 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/29 19:08:02 by fosuna-g         ###   ########.fr       */
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
	int		width;
	int		height;
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
	int		without_directions;
	char	**textures;
} t_map;

typedef struct s_ray_result
{
	double	dirX;
	double	dirY;
	double	stepX;
	double	stepY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	distance;
	double	hit_x;
	double	hit_y;
	int		side;
	char	type_wall;
} t_ray_result;

typedef struct s_vertical
{
	int		x;
	int		y_start;
	int		y_end;
	int		index;
	int		tex_x;
	double	tex_x_normalized;
} t_vertical;

typedef struct s_key_hook
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int key_right;
	int	key_left;
	int	key_shift;
	int	key_e;	
} t_key_hook;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	t_map		map;
	int			frame_count;
	int			minimap_scale;
	int			init_screen;
	t_data		texture[4];
	t_key_hook	keys;
}	t_game;

/* Hook functions */
int		xclose(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	rot_move(t_player *player, int direction);
void	player_move(t_game *game);
int		touch(double px, double py, t_game *game);
double	ray_dist(t_game *game, double dirX, double dirY);

/* Color functions */
int		add_shade(double distance, int color);
int		create_trgb(int t, int r, int g, int b);
int		is_light(int color);

/* Draw functions */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_torch(t_data *img, int x, int y, int flame_color);
void	draw_with_shading(t_data *data);
void	draw_square(t_data *img, int x, int y, int size, int color);
void	draw_square2(t_data *img, int x, int y, int size, int color);
void	draw_rectangle(t_data *img, int start_x, int start_y, int width, int height, int color);
void	draw_circle(t_data *img, int center_x, int center_y, int radius, int color);
void	draw_ray(t_game *game, double dirX, double dirY, int color);
void	draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color);
void	draw_multiple_rays(t_game *game, int num_rays);
void	draw_map(t_game *game);

/* Animation functions */
void	animate_torch_smooth(t_data *img, int x, int y, float time);
int		animation_loop(void *param);
void	clear_screen(t_game *game, int color);

/* Raycasting functions */
void	ray_casting_loop(t_game *game);
void	cast_ray_dda(t_game *game, t_ray_result *ray);
void	draw_vertical(t_game *game, t_vertical *v, t_ray_result ray);

/* Utils */
void    display_error(int n, char *msg);
void	clean_exit(int n, t_game *game, char *msg);
void	free_map(t_map *map);

/* Init functions */
t_map		init_map(void);
t_player	init_player(t_game *game);
t_game 		init_game(void);
void		init_keys(t_game *game);
int			load_textures(t_game *game);

/* Time functions */
void		wait(long time_to_sleep);
long int	get_time(void);
long int	get_diff_time(long int init_time);

#endif