/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:07:29 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:57:05 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == KEY_ESC)
		close_game(game);
	else if (keysym == KEY_W)
		game->keys.w = 1;
	else if (keysym == KEY_A)
		game->keys.a = 1;
	else if (keysym == KEY_S)
		game->keys.s = 1;
	else if (keysym == KEY_D)
		game->keys.d = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == KEY_W)
		game->keys.w = 0;
	else if (keysym == KEY_A)
		game->keys.a = 0;
	else if (keysym == KEY_S)
		game->keys.s = 0;
	else if (keysym == KEY_D)
		game->keys.d = 0;
	return (0);
}

void	set_player_animation(t_game *game, int direction)
{
	if (game->player.curr_anim != direction)
	{
		game->player.curr_anim = direction;
		game->player.curr_frame = 0;
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

void	set_player_static(t_game *game)
{
	game->player.state = PLAYER_STATE_STATIC;
	game->player.idle_timer = 0;
	render_tiles(game, game->player.x, game->player.y);
}
