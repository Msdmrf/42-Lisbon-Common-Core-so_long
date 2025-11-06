/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:46:21 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:57:13 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	render_move_text(t_game *game, char *moves_str)
{
	mlx_string_put(game->mlx, game->win, 9, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 19, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 9, 20, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 20, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 9, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 11, 21, 0x000000, moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
}

void	display_move_counter(t_game *game)
{
	char	*moves_str;
	char	*moves_num;

	moves_num = ft_itoa(game->player.moves);
	if (!moves_num)
		return ;
	moves_str = ft_strjoin("Moves: ", moves_num);
	free(moves_num);
	if (!moves_str)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
		TILE_SIZE * 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
		TILE_SIZE * 1, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img,
		TILE_SIZE * 2, 0);
	render_move_text(game, moves_str);
	free(moves_str);
}
