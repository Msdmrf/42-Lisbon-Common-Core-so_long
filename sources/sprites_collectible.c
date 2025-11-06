/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_collectible.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:02:03 by migusant          #+#    #+#             */
/*   Updated: 2025/11/05 18:57:16 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_collectible_sprites(t_game *game)
{
	char	*paths[ANIMATION_FRAMES];
	int		i;

	paths[0] = "textures/collectibles/frame_0.xpm";
	paths[1] = "textures/collectibles/frame_1.xpm";
	paths[2] = "textures/collectibles/frame_2.xpm";
	paths[3] = "textures/collectibles/frame_3.xpm";
	paths[4] = "textures/collectibles/frame_4.xpm";
	paths[5] = "textures/collectibles/frame_5.xpm";
	paths[6] = "textures/collectibles/frame_6.xpm";
	paths[7] = "textures/collectibles/frame_7.xpm";
	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		game->collectible.sprites[i] = mlx_xpm_file_to_image(game->mlx,
				paths[i], &game->img_width, &game->img_height);
		if (!game->collectible.sprites[i])
			return (ft_printf("Error\nCould not load collectible: %s\n",
					paths[i]), 0);
		i++;
	}
	return (1);
}
