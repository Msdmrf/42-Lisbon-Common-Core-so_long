/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:37:12 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:44:36 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->map[new_y][new_x] = EMPTY;
	game->collected++;
	ft_printf("Collected: %d/%d\n", game->collected, game->collectibles);
	if (game->collected == game->collectibles)
	{
		if (game->exit_img)
			mlx_destroy_image(game->mlx, game->exit_img);
		game->exit_img = mlx_xpm_file_to_image(game->mlx,
				"textures/exit_unlocked.xpm", &game->img_width,
				&game->img_height);
		if (!game->exit_img)
		{
			ft_printf("Error\nCould not load unlocked exit image.\n");
			return ;
		}
		render_tiles(game, game->exit_x, game->exit_y);
		ft_printf("All collectibles gathered! Exit is now unlocked!\n");
	}
}

void	handle_exit(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		ft_printf("Congratulations! You won in %d moves!\n",
			game->player_moves);
		close_game(game);
	}
	else
	{
		if (game->player_img)
			mlx_destroy_image(game->mlx, game->player_img);
		game->player_img = mlx_xpm_file_to_image(game->mlx,
				"textures/player_exit_locked.xpm", &game->img_width,
				&game->img_height);
		if (!game->player_img)
		{
			ft_printf("Error\nCould not load player exit locked image.\n");
			return ;
		}
		render_tiles(game, game->player_x, game->player_y);
		ft_printf("Collect all items first! (%d/%d)\n",
			game->collected, game->collectibles);
	}
}

void	handle_enemy(t_game *game)
{
	ft_printf("Game Over! You hit an enemy!\n");
	close_game(game);
}

void	handle_tiles(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == ENEMY_STATIC ||
		game->map[new_y][new_x] == ENEMY_HORIZONTAL ||
		game->map[new_y][new_x] == ENEMY_VERTICAL)
		handle_enemy(game);
	else if (game->map[new_y][new_x] == COLLECTIBLE)
		handle_collectible(game, new_x, new_y);
	else if (game->map[new_y][new_x] == EXIT)
		handle_exit(game);
}
