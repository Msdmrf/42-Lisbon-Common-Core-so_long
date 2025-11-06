/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:02:42 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:56:33 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	calculate_new_position(t_enemy *enemy, int *new_x, int *new_y)
{
	*new_x = enemy->x;
	*new_y = enemy->y;
	if (enemy->type == ENEMY_HORIZONTAL)
		*new_x += enemy->direction;
	else if (enemy->type == ENEMY_VERTICAL)
		*new_y += enemy->direction;
}

static int	is_valid_enemy_move(t_game *game, t_enemy *moving_enemy,
	int x, int y)
{
	int	i;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	if (game->map[y][x] == WALL || game->map[y][x] == COLLECTIBLE
		|| game->map[y][x] == EXIT)
		return (0);
	if (game->map[y][x] == ENEMY_STATIC || game->map[y][x] == ENEMY_HORIZONTAL
		|| game->map[y][x] == ENEMY_VERTICAL)
		return (0);
	if (moving_enemy != NULL)
	{
		i = 0;
		while (i < game->enemies.count)
		{
			if (&game->enemies.enemy[i] != moving_enemy
				&& game->enemies.enemy[i].x == x
				&& game->enemies.enemy[i].y == y)
				return (0);
			i++;
		}
	}
	return (1);
}

static void	update_enemy_position(t_game *game, t_enemy *enemy,
	int new_x, int new_y)
{
	game->map[enemy->y][enemy->x] = EMPTY;
	render_tiles(game, enemy->x, enemy->y);
	enemy->x = new_x;
	enemy->y = new_y;
	game->map[enemy->y][enemy->x] = enemy->type;
	render_tiles(game, enemy->x, enemy->y);
	if (game->player.x == enemy->x && game->player.y == enemy->y)
		handle_enemy_collision(game);
}

static void	move_enemy(t_game *game, t_enemy *enemy)
{
	int	new_x;
	int	new_y;
	int	old_anim;

	if (enemy->type == ENEMY_STATIC || enemy->state == ENEMY_STATE_STATIC)
		return ;
	old_anim = enemy->curr_anim;
	calculate_new_position(enemy, &new_x, &new_y);
	set_enemy_animation(enemy);
	if (!is_valid_enemy_move(game, enemy, new_x, new_y))
	{
		set_enemy_static_frame(enemy);
		enemy->direction *= -1;
		enemy->state = ENEMY_STATE_STATIC;
		enemy->static_timer = 0;
		return ;
	}
	if (old_anim != enemy->curr_anim)
		enemy->curr_frame = 0;
	update_enemy_position(game, enemy, new_x, new_y);
}

void	update_enemy(t_game *game)
{
	int	i;

	update_enemy_states(game);
	game->enemies.move_timer++;
	if (game->enemies.move_timer < ENEMY_TIMER)
		return ;
	game->enemies.move_timer = 0;
	i = 0;
	while (i < game->enemies.count)
	{
		if (game->enemies.enemy[i].state == ENEMY_STATE_MOVING
			&& game->enemies.enemy[i].direction != 0)
			move_enemy(game, &game->enemies.enemy[i]);
		i++;
	}
}
