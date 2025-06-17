/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:07:29 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:55:50 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	handle_movement(t_game *game, int *alternate)
{
	if ((game->keys.w && game->keys.s) || (game->keys.a && game->keys.d))
	{
		*alternate = 0;
		return ;
	}
	if ((game->keys.w && game->keys.a) || (game->keys.w && game->keys.d)
		|| (game->keys.s && game->keys.a) || (game->keys.s && game->keys.d))
		handle_dual_keys(game, alternate);
	else if (game->keys.w)
		handle_player(game, game->player_x, game->player_y - 1);
	else if (game->keys.s)
		handle_player(game, game->player_x, game->player_y + 1);
	else if (game->keys.a)
		handle_player(game, game->player_x - 1, game->player_y);
	else if (game->keys.d)
		handle_player(game, game->player_x + 1, game->player_y);
	else
		*alternate = 0;
}

static void	restore_player_sprite(t_game *game)
{
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &game->img_width, &game->img_height);
	if (!game->player_img)
	{
		ft_printf("Error\nCould not load original player image.\n");
		return ;
	}
}

void	handle_player(t_game *game, int new_x, int new_y)
{
	int	old_x;
	int	old_y;

	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] == WALL)
		return ;
	old_x = game->player_x;
	old_y = game->player_y;
	game->player_x = new_x;
	game->player_y = new_y;
	game->player_moves++;
	handle_tiles(game, new_x, new_y);
	if (game->map[old_y][old_x] == EXIT && game->map[new_y][new_x] != EXIT)
		restore_player_sprite(game);
	render_tiles(game, old_x, old_y);
	render_tiles(game, new_x, new_y);
	display_move_counter(game);
}

int	game_loop(t_game *game)
{
	static int	alternate;

	game->player_timer++;
	if (game->player_timer < PLAYER_TIMER)
	{
		update_enemy(game);
		return (0);
	}
	game->player_timer = 0;
	handle_movement(game, &alternate);
	return (0);
}
