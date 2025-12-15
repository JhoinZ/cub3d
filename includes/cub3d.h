/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:08:18 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/15 12:25:07 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1280
# define HEIGHT 720

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "key.h"
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

typedef enum e_game_state
{
	STATE_START,
	STATE_GAME,
	STATE_MENU,
	STATE_MAP
}	t_game_state;

typedef struct s_text_pos
{
	int	x;
	int	y;
	int	color;
}	t_text_pos;

typedef struct s_key_hook
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_right;
	int	key_left;
	int	key_e;
	int	key_m;
	int	key_tab;
}	t_key_hook;

typedef struct s_vertical
{
	int		x;
	int		y_start;
	int		y_end;
	int		index;
	int		tex_x;
	int		tex_y;
	int		a_start;
	int		a_end;
	double	tex_pos;
	double	step;
}	t_vertical;

typedef struct s_ray_result
{
	double	dir_x;
	double	dir_y;
	double	step_x;
	double	step_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	double	distance;
	double	hit_x;
	double	hit_y;
	int		side;
	char	type_wall;
}	t_ray_result;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	char	initial_dir;
	double	run;
}	t_player;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		tile_size;
	int		floor_color;
	int		ceiling_color;
	int		without_directions;
	int		elements_count;
	char	*textures[4];
}	t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_player		player;
	t_map			map;
	int				minimap_scale;
	t_data			texture[4];
	t_data			controls_menu;
	t_key_hook		keys;
	int				in_menu;
	int				init_screen;
	t_data			menu_background;
	int				menu_selection;
	t_game_state	state;
	t_game_state	prev_state;
	char			*line;
	int				fd_config;
}	t_game;

/* parsing functions */
void		ft_full_parsing(char **av, int ac, t_game *game);
void		ft_texture(char *data, t_game *game, char *id);
void		ft_color(char *data, t_game *game, char *id);
void		ft_create_map(char *map_buffer, t_game *game);
void		ft_validate_map(t_game *game);

/* setup/init helpers (parser -> game bridging) */
void		ft_setup_mlx_and_game(t_game *game);
void		ft_init_player_vectors(t_game *game);
void		load_wall_texture(t_game *game);
void		load_menu_texture(t_game *game, t_data *data);

/* Utils parsing */
int			ft_checkspace(char *line);
int			ft_endwith(char *str, char *suffix);
char		*ft_skipspace(char *str);
int			ft_check_argv(char **av, int ac);
void		ft_init_tools(t_game *game);

/* Utils textures */
int			check_walls(int *map_x, int *map_y, t_game *game);
double		distance_factor(double distance);
int			get_pixel_color(t_data *texture, int x, int y);
void		draw_tile(t_game *game, int x, int y, char tile);

/* Start menu */
void		print_start(t_game *game);
void		handle_start_menu_input(int keycode, t_game *game);
void		draw_bold_text(t_game *game, t_text_pos pos, char *text);

/* Hook functions */
int			xclose(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		player_actions(t_game *game);
void		rot_move(t_player *player, int direction);
void		player_move(t_game *game);

/* Color functions */
int			add_shade(double distance, int color);
int			create_trgb(int t, int r, int g, int b);
int			is_light(int color);
int			choose_color(int side);
int			get_pixel_color(t_data *texture, int x, int y);

/* Draw functions */
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_square(t_data *img, t_text_pos pos, int size);
void		draw_square2(t_data *img, t_text_pos pos, int size);
void		draw_rectangle(t_data *img, t_text_pos pos, int width, int height);
void		draw_vertical_line(t_game *game,
				t_text_pos pos, int start_y, int end_y);
void		draw_map1(t_game *game, int rel_width, int rel_begin);
void		draw_map2(t_game *game, int rel_height, int rel_begin);
void		print_map(t_game *game);
void		print_menu(t_game *game);
void		print_mini_map(t_game *game);

/* Animation functions */
void		clear_screen(t_game *game, int color);

/* Raycasting functions */
void		ray_casting_loop(t_game *game);
void		cast_ray_dda(t_game *game, t_ray_result *ray);
void		draw_vertical(t_game *game, t_vertical *v, t_ray_result ray);

/* Errors */
void		display_error(int n, char *msg);
void		ft_error(int error_code, t_game *game);
void		ft_error_light(int error_code);
void		ft_free_mem(t_game *game);
void		free_map(t_map *map);

#endif