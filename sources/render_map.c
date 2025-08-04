/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:40:33 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:47 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tiles(game, x, y);
			x++;
		}
		y++;
	}
	display_move_counter(game);
}

void	render_tile(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img,
		x * TILE_SIZE, y * TILE_SIZE);
}

void	render_tiles(t_game *game, int x, int y)
{
	int	i;

	render_tile(game, x, y, game->floor_img);
	if (game->map[y][x] == WALL)
		render_tile(game, x, y, game->wall_img);
	else if (game->map[y][x] == ENEMY_STATIC
		|| game->map[y][x] == ENEMY_HORIZONTAL
		|| game->map[y][x] == ENEMY_VERTICAL)
	{
		i = -1;
		while (++i < game->enemy.count)
		{
			if (game->enemy.patrol[i].x == x && game->enemy.patrol[i].y == y)
			{
				render_enemy_frame(game, x, y, &game->enemy.patrol[i]);
				break ;
			}
		}
	}
	else if (game->map[y][x] == COLLECTIBLE)
		render_collectible_frame(game, x, y);
	else if (game->map[y][x] == EXIT)
		render_tile(game, x, y, game->exit_img);
	if (game->player.x == x && game->player.y == y)
		render_player_frame(game, x, y);
}
