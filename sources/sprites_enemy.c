/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:27 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:24:00 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	load_enemy_base_paths(t_game *game, char **base_paths)
{
	char	path[100];
	int		anim;
	int		frame;
	char	*frame_str;

	anim = -1;
	while (++anim < ENEMY_ANIMATIONS)
	{
		frame = -1;
		while (++frame < ANIMATION_FRAMES)
		{
			ft_strlcpy(path, base_paths[anim], sizeof(path));
			frame_str = ft_itoa(frame);
			ft_strlcat(path, frame_str, sizeof(path));
			ft_strlcat(path, ".xpm", sizeof(path));
			free(frame_str);
			game->enemy.sprites[anim][frame] = mlx_xpm_file_to_image(game->mlx,
					path, &game->img_width, &game->img_height);
			if (!game->enemy.sprites[anim][frame])
				return (ft_printf("Error\nCould not load: %s\n", path), 0);
		}
	}
	return (1);
}

static int	load_enemy_static_paths(t_game *game, char **static_paths)
{
	int	anim;

	anim = 0;
	while (anim < DIRECTION_COUNT)
	{
		game->enemy.static_sprites[anim] = mlx_xpm_file_to_image(game->mlx,
				static_paths[anim], &game->img_width, &game->img_height);
		if (!game->enemy.static_sprites[anim])
			return (ft_printf("Error\nCould not load: %s\n",
					static_paths[anim]), 0);
		anim++;
	}
	return (1);
}

int	load_enemy_sprites(t_game *game)
{
	char	*base_paths[ENEMY_ANIMATIONS];
	char	*static_paths[DIRECTION_COUNT];

	base_paths[0] = "textures/enemies/idle_down/frame_";
	base_paths[1] = "textures/enemies/walk_down/frame_";
	base_paths[2] = "textures/enemies/walk_up/frame_";
	base_paths[3] = "textures/enemies/walk_left/frame_";
	base_paths[4] = "textures/enemies/walk_right/frame_";
	static_paths[0] = "textures/enemies/static_down.xpm";
	static_paths[1] = "textures/enemies/static_up.xpm";
	static_paths[2] = "textures/enemies/static_left.xpm";
	static_paths[3] = "textures/enemies/static_right.xpm";
	if (!load_enemy_base_paths(game, base_paths))
		return (0);
	if (!load_enemy_static_paths(game, static_paths))
		return (0);
	return (1);
}
