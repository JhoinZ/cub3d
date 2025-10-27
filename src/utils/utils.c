
#include "../../includes/cub3d.h"

void	display_error(int n, char *msg)
{
	ft_putstr_fd("\n========= \033[0;31mError\033[0m =========\n", 2);
	if (n == 0 && msg)
	{
		ft_putstr_fd("   ➤ ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	free_map(t_map *map)
{
	if (map && map->grid)
	{
		free(map->grid);
		map->grid = NULL;
	}
}

void	clean_exit(int n, t_game *game, char *msg)
{
	if (n != 0)
		display_error(0, msg);
	if (!game)
		exit(n);
	if (game->map.grid)
		free_map(&game->map);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_loop_end(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(n);
}
