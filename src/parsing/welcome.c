/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fosuna-g <fosuna-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:44:23 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/12/12 17:42:41 by fosuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bold_text(t_game *game, t_text_pos pos, char *text)
{
	mlx_string_put(game->mlx, game->win, pos.x, pos.y, pos.color, text);
	mlx_string_put(game->mlx, game->win, pos.x + 1, pos.y, pos.color, text);
	mlx_string_put(game->mlx, game->win, pos.x, pos.y + 1, pos.color, text);
	mlx_string_put(game->mlx, game->win, pos.x + 1, pos.y + 1, pos.color, text);
}

static void	ft_draw_menu_option(t_game *game, int option, int y, char *text)
{
	t_text_pos	pos;

	pos.x = WIDTH / 2 - 50;
	pos.y = y;
	if (game->menu_selection == option)
		pos.color = 0xFF0000;
	else
		pos.color = 0xFFFFFF;
	draw_bold_text(game, pos, text);
}

static void	ft_draw_all_menu_items(t_game *game)
{
	int	y;

	y = HEIGHT / 2 - 50;
	ft_draw_menu_option(game, 0, y, "> START GAME <");
	y += 70;
	ft_draw_menu_option(game, 1, y, "> CONTROLS <");
	y += 70;
	ft_draw_menu_option(game, 2, y, "> EXIT <");
}

void	print_start(t_game *game)
{
	t_text_pos	hint;

	clear_screen(game, 0x000000);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	if (game->menu_background.img)
		mlx_put_image_to_window(game->mlx, game->win,
			game->menu_background.img, 0, 0);
	ft_draw_all_menu_items(game);
	hint.x = WIDTH / 2 - 135;
	hint.y = HEIGHT - 50;
	hint.color = 0xFF0000;
	draw_bold_text(game, hint, "Use UP/DOWN arrows, ENTER to select");
}

void	handle_start_menu_input(int keycode, t_game *game)
{
	if (keycode == KEY_UP)
		game->menu_selection = (game->menu_selection - 1 + 3) % 3;
	else if (keycode == KEY_DOWN)
		game->menu_selection = (game->menu_selection + 1) % 3;
	else if (keycode == KEY_ENTER)
	{
		if (game->menu_selection == 0)
			game->state = STATE_GAME;
		else if (game->menu_selection == 1)
		{
			game->prev_state = STATE_START;
			game->state = STATE_MENU;
		}
		else if (game->menu_selection == 2)
			xclose(game);
	}
}
