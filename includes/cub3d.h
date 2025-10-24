/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:37 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/24 18:44:12 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080

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
	int	posX;
	int posY;
} t_player;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_data		img;
	t_player	player;
	int			frame_count;
}	t_game;

/* Hook functions */
int	xclose(t_game *game);
int	key_press(int keycode, t_game *game);
int	key_release(int keycode, t_game *game);

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
void	animate_torch_smooth(t_data *img, int x, int y, float time);
int		animation_loop(void *param);
void	clear_screen(t_game *game, int color);

/* Utils */
void    display_error(int n, char *msg);
void	clean_exit(int n, t_game *game, char *msg);

/* Time functions */
void		wait(long time_to_sleep);
long int	get_time(void);
long int	get_diff_time(long int init_time);

#endif