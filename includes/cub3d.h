/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:08:18 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/25 16:28:05 by fsaffiri         ###   ########.fr       */
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
#include "../MLX42/include/MLX42/MLX42.h"


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
	mlx_t		*mlx_ptr;
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
int ft_parse_file(const char *path, t_tools *tools);
char	*ft_parse_config(int fd, t_tools *tools);
int ft_create_map(char **lines, int nlines, t_tools *tools);
int ft_validate_map_closure(t_tools *tools);
void	ft_checkspace(char *line);


#endif