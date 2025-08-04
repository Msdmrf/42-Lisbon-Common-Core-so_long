/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:27:52 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:08 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	game_loop(t_game *game)
{
	static int	alternate;

	game->player.timer++;
	if (game->player.timer < PLAYER_TIMER)
	{
		update_enemy(game);
		update_collectible_sprites(game);
		update_enemy_sprites(game);
		update_player_sprites(game);
		return (0);
	}
	game->player.timer = 0;
	handle_movement(game, &alternate);
	return (0);
}
