/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:01:50 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:24:03 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_sprites(t_game *game)
{
	if (!load_basic_sprites(game))
		return (0);
	if (!load_animation_sprites(game))
		return (0);
	game->collectible.frame = 0;
	game->collectible.timer = 0;
	game->enemy.anim_timer = 0;
	init_player_animation(game);
	return (1);
}

int	load_basic_sprites(t_game *game)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"textures/static/wall.xpm", &game->img_width, &game->img_height);
	if (!game->wall_img)
		return (ft_printf("Error\nCould not load wall image.\n"), 0);
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"textures/static/floor.xpm", &game->img_width, &game->img_height);
	if (!game->floor_img)
		return (ft_printf("Error\nCould not load floor image.\n"), 0);
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"textures/static/exit_locked.xpm", &game->img_width,
			&game->img_height);
	if (!game->exit_img)
		return (ft_printf("Error\nCould not load exit image.\n"), 0);
	return (1);
}

int	load_animation_sprites(t_game *game)
{
	if (!load_collectible_sprites(game))
		return (0);
	if (!load_enemy_sprites(game))
		return (0);
	if (!load_player_sprites(game))
		return (0);
	return (1);
}

void	destroy_sprite_arrays(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PLAYER_ANIMATIONS)
	{
		j = 0;
		while (j < ANIMATION_FRAMES && game->player.sprites[i][j])
			mlx_destroy_image(game->mlx,
				game->player.sprites[i][j++]);
		j = 0;
		while (j < ANIMATION_FRAMES && game->player.exit_sprites[i][j])
			mlx_destroy_image(game->mlx,
				game->player.exit_sprites[i][j++]);
	}
	i = -1;
	while (++i < ENEMY_ANIMATIONS)
	{
		j = 0;
		while (j < ANIMATION_FRAMES && game->enemy.sprites[i][j])
			mlx_destroy_image(game->mlx,
				game->enemy.sprites[i][j++]);
	}
}

void	destroy_images(t_game *game)
{
	int	i;

	if (!game->mlx)
		return ;
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	destroy_sprite_arrays(game);
	i = -1;
	while (++i < DIRECTION_COUNT)
	{
		if (game->player.static_sprites[i])
			mlx_destroy_image(game->mlx, game->player.static_sprites[i]);
		if (game->player.exit_static_sprites[i])
			mlx_destroy_image(game->mlx, game->player.exit_static_sprites[i]);
		if (game->enemy.static_sprites[i])
			mlx_destroy_image(game->mlx, game->enemy.static_sprites[i]);
	}
	i = -1;
	while (++i < ANIMATION_FRAMES)
		if (game->collectible.sprites[i])
			mlx_destroy_image(game->mlx, game->collectible.sprites[i]);
}
