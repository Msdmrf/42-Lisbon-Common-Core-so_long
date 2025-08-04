/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:20 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:37 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_collectible_frame(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->collectible.sprites[game->collectible.frame],
		x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_player_static(t_game *game, int x, int y, int is_on_exit)
{
	if (is_on_exit)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.exit_static_sprites[game->player.last_direction],
			x * TILE_SIZE, y * TILE_SIZE);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.static_sprites[game->player.last_direction],
			x * TILE_SIZE, y * TILE_SIZE);
	}
}

static void	render_player_animated(t_game *game, int x, int y, int is_on_exit)
{
	if (is_on_exit)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.exit_sprites
		[game->player.current_anim][game->player.frame],
			x * TILE_SIZE, y * TILE_SIZE);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.sprites
		[game->player.current_anim][game->player.frame],
			x * TILE_SIZE, y * TILE_SIZE);
	}
}

void	render_player_frame(t_game *game, int x, int y)
{
	int	is_on_exit;

	is_on_exit = (game->player.x == game->exit_x
			&& game->player.y == game->exit_y);
	if (game->player.state == PLAYER_STATE_STATIC)
		render_player_static(game, x, y, is_on_exit);
	else
		render_player_animated(game, x, y, is_on_exit);
}

void	render_enemy_frame(t_game *game, int x, int y, t_enemy *enemy)
{
	if (enemy->state == ENEMY_STATE_STATIC)
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->enemy.static_sprites[enemy->static_frame],
			x * TILE_SIZE, y * TILE_SIZE);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win,
			game->enemy.sprites[enemy->current_anim][enemy->frame],
			x * TILE_SIZE, y * TILE_SIZE);
	}
}
