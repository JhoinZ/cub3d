/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:08:18 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/30 10:17:26 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include "../Libft/libft.h"
#include "../minilibx-linux/mlx.h"

#define RST			"\033[0m"    // Reset per tornare al colore normale
#define RED			"\033[1;31m" // Rosso brillante
#define GRN			"\033[1;32m" // Verde brillante
#define YLW			"\033[1;33m" // Giallo brillante
#define BLU			"\033[1;34m" // Blu brillante
#define MGT			"\033[1;35m" // Magenta brillante
#define CYN			"\033[1;36m" // Ciano brillante
#define WIT			"\033[1;37m" // Bianco brillante

typedef struct	s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;


typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	initial_dir;
}	t_player;

typedef struct	s_tools
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*tex_no;
	char		*tex_so;
	char		*tex_we;
	char		*tex_ea;
	t_rgb		floor_color;
	t_rgb		ceil_color;
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

#endif