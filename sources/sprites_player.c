/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:15 by migusant          #+#    #+#             */
/*   Updated: 2025/08/04 19:24:07 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	load_animated_sprites(t_game *game, char **base_paths)
{
	char	path[100];
	int		anim;
	int		frame;
	char	*frame_str;

	anim = -1;
	while (++anim < PLAYER_ANIMATIONS)
	{
		frame = -1;
		while (++frame < ANIMATION_FRAMES)
		{
			ft_strlcpy(path, base_paths[anim], sizeof(path));
			frame_str = ft_itoa(frame);
			ft_strlcat(path, frame_str, sizeof(path));
			ft_strlcat(path, ".xpm", sizeof(path));
			free(frame_str);
			game->player.sprites[anim][frame] = mlx_xpm_file_to_image
				(game->mlx, path, &game->img_width, &game->img_height);
			if (!game->player.sprites[anim][frame])
				return (ft_printf("Error\nCould not load: %s\n", path), 0);
		}
	}
	return (1);
}

static int	load_static_sprites(t_game *game, char **static_paths)
{
	int	anim;

	anim = 0;
	while (anim < DIRECTION_COUNT)
	{
		game->player.static_sprites[anim] = mlx_xpm_file_to_image(game->mlx,
				static_paths[anim], &game->img_width, &game->img_height);
		if (!game->player.static_sprites[anim])
			return (ft_printf("Error\nCould not load: %s\n",
					static_paths[anim]), 0);
		anim++;
	}
	return (1);
}

static int	load_exit_locked_animated(t_game *game, char **base_paths)
{
	char	path[100];
	int		anim;
	int		frame;
	char	*frame_str;

	anim = -1;
	while (++anim < PLAYER_ANIMATIONS)
	{
		frame = -1;
		while (++frame < ANIMATION_FRAMES)
		{
			ft_strlcpy(path, "textures/player/exit_locked/", sizeof(path));
			ft_strlcat(path, base_paths[anim] + 16, sizeof(path));
			frame_str = ft_itoa(frame);
			ft_strlcat(path, frame_str, sizeof(path));
			ft_strlcat(path, ".xpm", sizeof(path));
			free(frame_str);
			game->player.exit_sprites[anim][frame] = mlx_xpm_file_to_image
				(game->mlx, path, &game->img_width, &game->img_height);
			if (!game->player.exit_sprites[anim][frame])
				return (ft_printf("Error\nCould not load: %s\n", path), 0);
		}
	}
	return (1);
}

static int	load_exit_locked_static(t_game *game, char **static_paths)
{
	char	path[100];
	int		anim;

	anim = -1;
	while (++anim < DIRECTION_COUNT)
	{
		ft_strlcpy(path, "textures/player/exit_locked/", sizeof(path));
		ft_strlcat(path, static_paths[anim] + 16, sizeof(path));
		game->player.exit_static_sprites[anim] = mlx_xpm_file_to_image
			(game->mlx, path, &game->img_width, &game->img_height);
		if (!game->player.exit_static_sprites[anim])
			return (ft_printf("Error\nCould not load: %s\n", path), 0);
	}
	return (1);
}

int	load_player_sprites(t_game *game)
{
	char	*base_paths[PLAYER_ANIMATIONS];
	char	*static_paths[DIRECTION_COUNT];

	base_paths[0] = "textures/player/idle_down/frame_";
	base_paths[1] = "textures/player/idle_up/frame_";
	base_paths[2] = "textures/player/idle_left/frame_";
	base_paths[3] = "textures/player/idle_right/frame_";
	base_paths[4] = "textures/player/walk_down/frame_";
	base_paths[5] = "textures/player/walk_up/frame_";
	base_paths[6] = "textures/player/walk_left/frame_";
	base_paths[7] = "textures/player/walk_right/frame_";
	static_paths[0] = "textures/player/static_down.xpm";
	static_paths[1] = "textures/player/static_up.xpm";
	static_paths[2] = "textures/player/static_left.xpm";
	static_paths[3] = "textures/player/static_right.xpm";
	if (!load_animated_sprites(game, base_paths))
		return (0);
	if (!load_static_sprites(game, static_paths))
		return (0);
	if (!load_exit_locked_animated(game, base_paths))
		return (0);
	if (!load_exit_locked_static(game, static_paths))
		return (0);
	return (1);
}
