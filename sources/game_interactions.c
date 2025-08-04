/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:37:12 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:05 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->map[new_y][new_x] = EMPTY;
	game->collectible.collected++;
	ft_printf("Collected: %d/%d\n", game->collectible.collected,
		game->collectible.count);
	if (game->collectible.collected == game->collectible.count)
	{
		unlock_exit(game);
		ft_printf("All collectibles gathered! Exit is now unlocked!\n");
	}
}

void	handle_enemy_collision(t_game *game)
{
	ft_printf("Game Over! You hit an enemy!\n");
	close_game(game);
}

void	handle_exit(t_game *game)
{
	if (game->collectible.collected == game->collectible.count)
	{
		ft_printf("Congratulations! You won in %d moves!\n",
			game->player.moves);
		close_game(game);
	}
	else
	{
		ft_printf("Collect all items first! (%d/%d)\n",
			game->collectible.collected, game->collectible.count);
	}
}

void	handle_tiles(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == ENEMY_STATIC ||
		game->map[new_y][new_x] == ENEMY_HORIZONTAL ||
		game->map[new_y][new_x] == ENEMY_VERTICAL)
		handle_enemy_collision(game);
	else if (game->map[new_y][new_x] == COLLECTIBLE)
		handle_collectible(game, new_x, new_y);
	else if (game->map[new_y][new_x] == EXIT)
		handle_exit(game);
}

void	unlock_exit(t_game *game)
{
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"textures/static/exit_unlocked.xpm", &game->img_width,
			&game->img_height);
	if (!game->exit_img)
	{
		ft_printf("Error\nCould not load unlocked exit image.\n");
		return ;
	}
	render_tiles(game, game->exit_x, game->exit_y);
}
