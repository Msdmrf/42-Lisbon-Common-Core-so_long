/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:07:29 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:35 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_player_animation(t_game *game)
{
	game->player.current_anim = ANIM_IDLE_DOWN;
	game->player.last_direction = DIRECTION_DOWN;
	game->player.frame = 0;
	game->player.state = PLAYER_STATE_IDLE;
	game->player.anim_timer = 0;
	game->player.idle_timer = 0;
}

void	set_player_static(t_game *game)
{
	game->player.state = PLAYER_STATE_STATIC;
	game->player.idle_timer = 0;
	render_tiles(game, game->player.x, game->player.y);
}

void	set_player_animation(t_game *game, int direction)
{
	if (game->player.current_anim != direction)
	{
		game->player.current_anim = direction;
		game->player.frame = 0;
	}
	game->player.state = PLAYER_STATE_MOVING;
	game->player.idle_timer = 0;
	if (direction == ANIM_WALK_DOWN)
		game->player.last_direction = DIRECTION_DOWN;
	else if (direction == ANIM_WALK_UP)
		game->player.last_direction = DIRECTION_UP;
	else if (direction == ANIM_WALK_LEFT)
		game->player.last_direction = DIRECTION_LEFT;
	else if (direction == ANIM_WALK_RIGHT)
		game->player.last_direction = DIRECTION_RIGHT;
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	return (0);
}
