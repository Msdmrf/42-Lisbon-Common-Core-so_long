/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:28 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:23:10 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putendl_fd("Error: MLX initialization failed.", 2);
		return (0);
	}
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, WINDOW_TITLE);
	if (!game->win)
	{
		ft_putendl_fd("Error: Window creation failed.", 2);
		return (0);
	}
	return (1);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	close_game(t_game *game)
{
	if (game->enemy.patrol)
		free(game->enemy.patrol);
	if (game->map)
		free_map(game->map);
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	if (!load_map(&game, argv[1]))
		return (close_game(&game), 1);
	if (!init_window(&game))
		return (close_game(&game), 1);
	if (!load_sprites(&game))
		return (close_game(&game), 1);
	init_enemy_patrol(&game);
	render_map(&game);
	ft_printf("Game initialized successfully!\n");
	ft_printf("Hold WASD to move continuously, ESC or [X] to quit.\n");
	ft_printf("Avoid enemies or you'll lose the game!\n");
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
