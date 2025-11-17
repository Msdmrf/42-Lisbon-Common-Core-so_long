/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_system.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:07:29 by migusant          #+#    #+#             */
/*   Updated: 2025/11/07 12:32:39 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_game(game);
	else if (keysym == XK_w)
		game->keys.w = 1;
	else if (keysym == XK_a)
		game->keys.a = 1;
	else if (keysym == XK_s)
		game->keys.s = 1;
	else if (keysym == XK_d)
		game->keys.d = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->keys.w = 0;
	else if (keysym == XK_a)
		game->keys.a = 0;
	else if (keysym == XK_s)
		game->keys.s = 0;
	else if (keysym == XK_d)
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
