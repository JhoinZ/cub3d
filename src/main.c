/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/27 13:52:48 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

t_player	init_player(t_game *game)
{
	t_player player;

	(void)game;
	player.posX = 650.0f;
	player.posY = 530.0f;
	player.dirX = 0;
	player.dirY = -1;
	player.planeX = 0.66f;
	player.planeY = 0;
	player.rot_speed = 0.07f;
	player.move_speed = (WIDTH * HEIGHT) * 1.0e-5;
	return (player);
}

t_map	init_map()
{
	t_map	map;

	map.width = 9;
	map.height = 7;
	map.grid = malloc(sizeof(char *) * map.height);
	map.grid[0] = "111111111";
	map.grid[1] = "100000001";
	map.grid[2] = "100000101";
	map.grid[3] = "100000001";
	map.grid[4] = "100100001";
	map.grid[5] = "100010001";
	map.grid[6] = "111111111";
	if ((WIDTH / map.width) > (HEIGHT / map.height))
		map.tile_size = (HEIGHT / map.height);
	else
		map.tile_size = (WIDTH / map.width);
	return (map);
}

/* int	main(void)
{
	t_game	game;

	game = init_game();
	
	//draw_with_shading(&game.img);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	//mlx_hook(game.win, 2, 1L<<0, windows_close, &game); // this is for keydown
	mlx_key_hook(game.win, key_hook, &game); // this is for keyup
	
	game.player_x = 400;
	game.player_y = 300;
	game.frame_count = 0;
	
	mlx_loop_hook(game.mlx, animation_loop, &game);
	mlx_loop(game.mlx);
	return (0);
} */

/* #define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(void)
{
	double posX = 22, posY = 12; // Position vector
	double dirX = -1, dirY = 0; // Direction vector
	double planeX = 0, planeY = 0.66; // 2d raycaster verssion of camera pllane
	
	double time = 0; // time of current frame
	double oldTime = 0; // time of previous frame
	t_game	game;

	game = init_game();
	while (!done())
	{
		for(int x = 0; x < WIDTH; x++)
		{
			double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space is between -1 and 1
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			
			//which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;
			
			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
			double perpWallDist;
			
			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
				}
				else
				{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			} 
		}
	}
	
} */

void	draw_map(t_game *game)
{
	int i;
	int	j;
	int	rel_width = game->map.tile_size;
	int	rel_hegith = (HEIGHT / game->map.height);
	int	rel_begin = (WIDTH / 2) - (rel_width * game->map.width / 2);
	
	i = 0;
	(void)game;
	while (i < game->map.width)
	{
		j = 0;
		while (j < game->map.height)
		{
			rel_width = i * game->map.tile_size + rel_begin;
			rel_hegith = j * game->map.tile_size;
			if (game->map.grid[j][i] > '0')
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_hegith, game->map.tile_size, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_multiple_rays(t_game *game, int num_rays)
{
	double	half_fov = 0.66 / 2;
	double	center_angle = atan2(-game->player.dirY, game->player.dirX);
	double	left_angle = center_angle - half_fov;
	double	angle_step = 2 * half_fov / (num_rays - 1);
	int i = 0;
	while (i < num_rays)
	{
		double ray_angle = left_angle + i * angle_step;
		double ray_dirX = cos(ray_angle);
		double ray_dirY = -sin(ray_angle);
		draw_ray(game, ray_dirX, ray_dirY, 0x00FF00);
		i++;
	}
}

void	draw_vertical_line(t_game *game, int x, int length, int color)
{
	int i;
	int y;

	y = HEIGHT / 2;
	i = 0;
	while (i < (length / 2))
	{
		my_mlx_pixel_put(&game->img, x, y + i, color);
		my_mlx_pixel_put(&game->img, x, y - i, color);
		i++;
	}
	
}

/* void	draw_scene(t_game *game, int num_rays)
{
	double	half_fov = 0.66 / 2;
	double	center_angle = atan2(-game->player.dirY, game->player.dirX);
	double	left_angle = center_angle - half_fov;
	double	angle_step = 2 * half_fov / (num_rays - 1);
	int		i = 0;
	while (i < num_rays)
	{
		double ray_angle = left_angle + i * angle_step;
		double ray_dirX = cos(ray_angle);
		double ray_dirY = -sin(ray_angle);
		double dist_ray = ray_dist(game, ray_dirX, ray_dirY, center_angle);
		draw_line(game, i * (WIDTH / num_rays), (game->map.tile_size / dist_ray) * (WIDTH / 2), 0xFFFFFF);
		i++;
	}
} */

t_ray_result	cast_ray_dda(t_game *game, double ray_dirX, double ray_dirY)
{
	t_ray_result	result;
    
    // Player's map position
    int mapX = (int)game->player.posX;
    int mapY = (int)game->player.posY;
    
    // Length of ray from current position to next x or y-side
    double deltaDistX = fabs(1 / ray_dirX);
    double deltaDistY = fabs(1 / ray_dirY);
    
    // Direction to step in x or y direction (either +1 or -1)
    int stepX, stepY;
    
    // Length of ray from one side to next in map
    double sideDistX, sideDistY;
    
    // Calculate step and initial sideDist
    if (ray_dirX < 0) {
        stepX = -1;
        sideDistX = (game->player.posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
    }
    
    if (ray_dirY < 0) {
        stepY = -1;
        sideDistY = (game->player.posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
    }
    
    // Perform DDA
    int hit = 0;
    int side; // 0 for x-side, 1 for y-side
    
    while (hit == 0) {
        // Jump to next map square
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        
        // Check if ray has hit a wall
        if (game->map.grid[mapY][mapX] > '0')
            hit = 1;
    }
    
    // Calculate distance projected on camera direction
    if (side == 0)
        result.distance = (mapX - game->player.posX + (1 - stepX) / 2) / ray_dirX;
    else
        result.distance = (mapY - game->player.posY + (1 - stepY) / 2) / ray_dirY;
    
    result.side = side;
    result.hit_x = game->player.posX + result.distance * ray_dirX;
    result.hit_y = game->player.posY + result.distance * ray_dirY;
    
	return (result);
}

int choose_color(int side)
{
    if (side == 0) 
        return 0xFF0000; // Red for x-side (vertical walls)
    else 
        return 0x00FF00; // Green for y-side (horizontal walls)
}

void	cast_rays(t_game *game)
{
	int	x;
	double	cameraX;
	double	ray_dirX;
	double	ray_dirY;
	int		line_height;
	
	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		ray_dirX = game->player.dirX + game->player.planeX * cameraX;
		ray_dirY = game->player.dirY + game->player.planeY * cameraX;
		t_ray_result ray = cast_ray_dda(game, ray_dirX, ray_dirY);
		line_height = (int)(HEIGHT / ray.distance);
		draw_vertical_line(game, cameraX, line_height, choose_color(ray.side));
		x++;
	}
}


int	game_loop(void *param)
{
	t_game			*game;
	int				size_player;
	
	game = (t_game *)param;
	clear_screen(game, 0x00224466);
	if (DEBUG)
	{
		draw_map(game);
		size_player = (int)(game->map.tile_size / (game->player.move_speed * 1.5));
		draw_square(&game->img, (int)(game->player.posX - (size_player / 2)),
				(int)(game->player.posY - (size_player / 2)), size_player, 0x00FF00);
		draw_multiple_rays(game, WIDTH);
	}
	else
	{
		cast_rays(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;
	
	game = init_game();
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	game.map = init_map();
	game.player = init_player(&game);
	
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
