/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:49:57 by fosuna-g          #+#    #+#             */
/*   Updated: 2025/12/12 11:41:40 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// struct timeval {
//   time_t        tv_sec;   // Seconds
//   suseconds_t   tv_usec;  // microseconds
// };

/* It's a sleep function with a better control of the milliseconds */
void	wait(long time_to_sleep)
{
	long	wake_up_time;

	if (time_to_sleep <= 0)
		return ;
	wake_up_time = get_time() + time_to_sleep;
	while (get_time() < wake_up_time)
		usleep(100);
}

/* Returns the time pased since  1970 in milliseconds */
long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((long int)(time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* It returns the miliseconds between the time passed by argument and
 the actual time */
long int	get_diff_time(long int init_time)
{
	long int	curr_time;

	curr_time = get_time();
	if (curr_time == 0)
		return (0);
	return (curr_time - init_time);
}

void	display_fps(t_game *game)
{
	long int	current_time;
	long int	delta;
	char		*fps_str;

	current_time = get_time();
	delta = current_time - game->last_frame_time;
	if (delta > 0)
		game->fps = 1000 / delta;
	game->last_frame_time = current_time;
	fps_str = ft_itoa(game->fps);
	if (fps_str)
	{
		mlx_string_put(game->mlx, game->win,
			WIDTH - 50, HEIGHT - 20, 0x00FF00,
			fps_str);
		free(fps_str);
	}
}
