
#include "../../includes/cub3d.h"

int	load_textures(t_game *game)
{
	int	i;
	int	width;
	int	height;
	
	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx, 
			game->map.textures[i], &width, &height);
		if (!game->texture[i].img)
			return (0); // Error loading texture
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
			&game->texture[i].bits_per_pixel, &game->texture[i].line_length,
			&game->texture[i].endian);
		game->texture[i].width = width;
		game->texture[i].height = height;
		i++;
	}
	return (1);
}

void	init_keys(t_game *game)
{
	game->keys.key_a = 0;
	game->keys.key_d = 0;
	game->keys.key_e = 0;
	game->keys.key_left = 0;
	game->keys.key_right = 0;
	game->keys.key_s = 0;
	game->keys.key_shift = 0;
	game->keys.key_w = 0;
}

t_game init_game(void)
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
									&game.img.line_length, &game.img.endian);
	game.init_screen = 0;
	init_keys(&game);
	return (game);
}

t_player	init_player(t_game *game)
{
	t_player	player;

	player.posX = game->map.tile_size * 3 - (game->map.tile_size / 2);
	player.posY = game->map.tile_size * 4 - (game->map.tile_size / 2);
	player.dirX = 0;
	player.dirY = -1;
	player.planeX = 0.66f;
	player.planeY = 0;
	player.rot_speed = 0.07f;
	player.move_speed = game->map.tile_size / 8;
	return (player);
}

t_map	init_map()
{
	t_map	map;

	map.width = 24;
	map.height = 24;
	map.grid = malloc(sizeof(char *) * map.height);
	map.grid[0] = "111111111111111111111111";
	map.grid[1] = "100000000000000000000001";
	map.grid[2] = "100000000000000000000001";
	map.grid[3] = "100000000000000000000001";
	map.grid[4] = "100000222220000303030001";
	map.grid[5] = "100000200020000000300001";
	map.grid[6] = "100000200020000300030001";
	map.grid[7] = "100000200020000000000001";
	map.grid[8] = "100000220220000303030001";
	map.grid[9] = "100000000000000000000001";
	map.grid[10] = "100000000000000000000001";
	map.grid[11] = "100000000000000000000001";
	map.grid[12] = "100000000000000000000001";
	map.grid[13] = "100000000000000000000001";
	map.grid[14] = "100000000000000000000001";
	map.grid[15] = "100000000000000000000001";
	map.grid[16] = "144444444000000000000001";
	map.grid[17] = "140400004000000000000001";
	map.grid[18] = "140000504000000000000001";
	map.grid[19] = "140400004000000000000001";
	map.grid[20] = "140444444000000000000001";
	map.grid[21] = "140000000000000000000001";
	map.grid[22] = "144444444000000000000001";
	map.grid[23] = "111111111111111111111111";
	map.ceiling_color = 0x0074D4FF;
	map.floor_color = 0x003F3F46;
	if ((WIDTH / map.width) > (HEIGHT / map.height))
		map.tile_size = (HEIGHT / map.height);
	else
		map.tile_size = (WIDTH / map.width);
	return (map);
}
