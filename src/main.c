/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 08:46:46 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/10/24 19:59:27 by fosuna-g         ###   ########.fr       */
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

#define mapWidth 16
#define mapHeight 9

int worldMap[mapHeight][mapWidth]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_map(t_game *game)
{
	int i;
	int	j;
	int	rel_width = (WIDTH / mapWidth);
	int	rel_hegith = (HEIGHT / mapHeight);
	
	printf("%d, %d\n", rel_width, rel_hegith);
	i = 0;
	(void)game;
	while (i < mapWidth)
	{
		j = 0;
		while (j < mapHeight)
		{
			rel_width = i * (WIDTH / mapWidth);
			rel_hegith = j * (HEIGHT / mapHeight);
			/* if (worldMap[j][i] > 0)
				draw_square(&game->img, rel_width, rel_hegith, (WIDTH / mapWidth) - 1, 0xFF81D8D0);	
			else
				draw_square(&game->img, rel_width, rel_hegith, (WIDTH / mapWidth) - 1, 0xFF084D6E);	
			draw_square2(&game->img, rel_width, rel_hegith, (WIDTH / mapWidth) - 1, 0xFFFFFF); */
			j++;
		}
		i++;
	}
}

int	game_loop(void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	clear_screen(game, 0x00224466);
	draw_square(&game->img, game->player.posX, game->player.posY, 40, 0x00FF00);
	draw_map(game);
	
	mlx_put_image_to_window(&game->mlx, &game->win, &game->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_game	game;
	
	game = init_game();
	mlx_hook(&game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(&game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, EVENT_CLOSE_BTN, 1L<<0, xclose, &game);
	
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
