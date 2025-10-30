/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:08:18 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 12:47:02 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.141592653589
# define DEBUG 0

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define RST			"\033[0m"    // Reset per tornare al colore normale
# define RED			"\033[1;31m" // Rosso brillante
# define GRN			"\033[1;32m" // Verde brillante
# define YLW			"\033[1;33m" // Giallo brillante
# define BLU			"\033[1;34m" // Blu brillante
# define MGT			"\033[1;35m" // Magenta brillante
# define CYN			"\033[1;36m" // Ciano brillante
# define WIT			"\033[1;37m" // Bianco brillante

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	initial_dir;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_tools
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;
	t_rgb		floor_color;
	t_rgb		ceil_color;
	t_img		img_buffer;
	char		**map_grid;
	int			map_height;
	int			map_width;
	t_player	player;
	bool		status;
	int			elements_count;
}	t_tools;

/* parsing functions */
void	ft_full_parsing(char **av, int ac, t_tools *tools);
void	ft_texture(char *data, t_tools *tools, char *id);
void	ft_color(char *data, t_tools *tools, char *id);
void	ft_create_map(char *map_buffer, t_tools *tools);
void	ft_validate_map(t_tools *tools);

/* utils parsing */
int		ft_checkspace(char *line);
int		ft_endwith(char *str, char *suffix);
char	*ft_skipspace(char *str);
int		ft_check_argv(char **av, int ac);
void	ft_init_tools(t_tools *tools);

/* Error */
void	ft_error(int error_code, t_tools *tools);
void	ft_error_light(int error_code);
void	ft_free_mem(t_tools *tools);


# define WIDTH 1920
# define HEIGHT 1080
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
	char	*textures[4];
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
	int		tex_y;
	int		tex_pos;
	char	*pixel_addr;
	int		step;
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
void	player_actions(t_game *game);
void	rot_move(t_player *player, int direction);
void	player_move(t_game *game);
int		touch(double px, double py, t_game *game);
double	ray_dist(t_game *game, double dirX, double dirY);

/* Color functions */
int		add_shade(double distance, int color);
int		create_trgb(int t, int r, int g, int b);
int		is_light(int color);
int 	choose_color(int side);

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
void		load_textures(t_game *game);

/* Time functions */
void		wait(long time_to_sleep);
long int	get_time(void);
long int	get_diff_time(long int init_time);

#endif