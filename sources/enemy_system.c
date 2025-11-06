/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:46:54 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:56:36 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	init_enemy(t_enemy *enemy, int x, int y, char type)
{
	enemy->x = x;
	enemy->y = y;
	enemy->type = type;
	if (type == ENEMY_STATIC)
	{
		enemy->state = ENEMY_STATE_STATIC;
		enemy->direction = 0;
	}
	else
	{
		enemy->state = ENEMY_STATE_MOVING;
		enemy->direction = 1;
	}
	enemy->curr_anim = ENEMY_ANIM_IDLE_DOWN;
	enemy->curr_frame = 0;
	enemy->static_frame = DIRECTION_DOWN;
	enemy->static_timer = 0;
}

void	init_enemies(t_game *game)
{
	int	i;
	int	x;
	int	y;

	game->enemies.enemy = malloc(sizeof(t_enemy) * game->enemies.count);
	if (!game->enemies.enemy)
		return ;
	i = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == ENEMY_STATIC
				|| game->map[y][x] == ENEMY_HORIZONTAL
				|| game->map[y][x] == ENEMY_VERTICAL)
				init_enemy(&game->enemies.enemy[i++], x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}

void	update_enemy_states(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemies.count)
	{
		if (game->enemies.enemy[i].state == ENEMY_STATE_STATIC)
		{
			game->enemies.enemy[i].static_timer++;
			if (game->enemies.enemy[i].static_timer >= ENEMY_STATIC_DELAY)
			{
				game->enemies.enemy[i].state = ENEMY_STATE_MOVING;
				game->enemies.enemy[i].static_timer = 0;
			}
		}
		i++;
	}
}

void	set_enemy_animation(t_enemy *enemy)
{
	if (enemy->type == ENEMY_HORIZONTAL)
	{
		if (enemy->direction > 0)
			enemy->curr_anim = ENEMY_ANIM_WALK_RIGHT;
		else
			enemy->curr_anim = ENEMY_ANIM_WALK_LEFT;
	}
	else if (enemy->type == ENEMY_VERTICAL)
	{
		if (enemy->direction > 0)
			enemy->curr_anim = ENEMY_ANIM_WALK_DOWN;
		else
			enemy->curr_anim = ENEMY_ANIM_WALK_UP;
	}
}

void	set_enemy_static_frame(t_enemy *enemy)
{
	if (enemy->type == ENEMY_HORIZONTAL)
	{
		if (enemy->direction > 0)
			enemy->static_frame = DIRECTION_DOWN;
		else
			enemy->static_frame = DIRECTION_UP;
	}
	else if (enemy->type == ENEMY_VERTICAL)
	{
		if (enemy->direction > 0)
			enemy->static_frame = DIRECTION_LEFT;
		else
			enemy->static_frame = DIRECTION_RIGHT;
	}
}
