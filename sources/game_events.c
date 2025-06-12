/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:25:36 by migusant          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:43 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	return (0);
}

void	handle_tiles(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->map[new_y][new_x] = EMPTY;
		game->collected++;
		ft_printf("Collected: %d/%d\n", game->collected, game->collectibles);
	}
	else if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collected == game->collectibles)
		{
			ft_printf("Congratulations! You won in %d moves!\n", game->moves);
			close_game(game);
		}
		else
			ft_printf("Collect all items first! (%d/%d)\n",
				game->collected, game->collectibles);
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
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	handle_tiles(game, new_x, new_y);
	render_tiles(game, old_x, old_y);
	render_tiles(game, new_x, new_y);
}

int	game_loop(t_game *game)
{
	static int	alternate = 0;

	game->move_counter++;
	if (game->move_counter < MOVEMENT_SPEED)
		return (0);
	game->move_counter = 0;
	handle_movement(game, &alternate);
	return (0);
}
