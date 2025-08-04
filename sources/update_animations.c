/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:32:59 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:24:10 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	render_all_by_type(t_game *game, char type)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (type == COLLECTIBLE && game->map[y][x] == COLLECTIBLE)
				render_tiles(game, x, y);
			else if (type != COLLECTIBLE && (game->map[y][x] == ENEMY_STATIC
				|| game->map[y][x] == ENEMY_HORIZONTAL
				|| game->map[y][x] == ENEMY_VERTICAL))
				render_tiles(game, x, y);
			x++;
		}
		y++;
	}
}

void	update_collectible_sprites(t_game *game)
{
	game->collectible.timer++;
	if (game->collectible.timer >= COLLECTIBLE_TIMER)
	{
		game->collectible.timer = 0;
		game->collectible.frame = (game->collectible.frame + 1)
			% ANIMATION_FRAMES;
		render_all_by_type(game, COLLECTIBLE);
	}
}

static void	handle_static_to_idle_transition(t_game *game)
{
	game->player.idle_timer++;
	if (game->player.idle_timer >= PLAYER_IDLE_DELAY)
	{
		game->player.state = PLAYER_STATE_IDLE;
		game->player.frame = 0;
		game->player.anim_timer = 0;
		if (game->player.last_direction == DIRECTION_DOWN)
			game->player.current_anim = ANIM_IDLE_DOWN;
		else if (game->player.last_direction == DIRECTION_UP)
			game->player.current_anim = ANIM_IDLE_UP;
		else if (game->player.last_direction == DIRECTION_LEFT)
			game->player.current_anim = ANIM_IDLE_LEFT;
		else if (game->player.last_direction == DIRECTION_RIGHT)
			game->player.current_anim = ANIM_IDLE_RIGHT;
	}
}

void	update_player_sprites(t_game *game)
{
	if (game->player.state == PLAYER_STATE_STATIC)
		handle_static_to_idle_transition(game);
	else if (game->player.state == PLAYER_STATE_IDLE)
	{
		game->player.anim_timer++;
		if (game->player.anim_timer >= PLAYER_TIMER)
		{
			game->player.anim_timer = 0;
			game->player.frame = (game->player.frame + 1) % ANIMATION_FRAMES;
			render_tiles(game, game->player.x, game->player.y);
		}
	}
	else if (game->player.state == PLAYER_STATE_MOVING)
	{
		game->player.anim_timer++;
		if (game->player.anim_timer >= PLAYER_TIMER)
		{
			game->player.anim_timer = 0;
			game->player.frame = (game->player.frame + 1) % ANIMATION_FRAMES;
			render_tiles(game, game->player.x, game->player.y);
		}
	}
}

void	update_enemy_sprites(t_game *game)
{
	int	i;

	game->enemy.anim_timer++;
	if (game->enemy.anim_timer >= ENEMY_TIMER)
	{
		game->enemy.anim_timer = 0;
		i = 0;
		while (i < game->enemy.count)
		{
			game->enemy.patrol[i].frame = (game->enemy.patrol[i].frame + 1)
				% ANIMATION_FRAMES;
			i++;
		}
		render_all_by_type(game, ENEMY_STATIC);
	}
}
