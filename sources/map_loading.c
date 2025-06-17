/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:19:34 by migusant          #+#    #+#             */
/*   Updated: 2025/06/17 16:37:57 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static char	**allocate_map(int lines)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	map[lines] = NULL;
	return (map);
}

static int	read_map_lines(t_game *game, char *filename)
{
	int		fd;
	int		i;
	char	*line;
	size_t	len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map[i] = line;
		if (i == 0)
			game->map_width = ft_strlen(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	load_map(t_game *game, char *filename)
{
	game->map_height = count_lines(filename);
	if (game->map_height <= 0)
	{
		ft_putendl_fd("Error\nCould not read map file.", 2);
		return (0);
	}
	game->map = allocate_map(game->map_height);
	if (!game->map)
	{
		ft_putendl_fd("Error\nMemory allocation failed.", 2);
		return (0);
	}
	if (!read_map_lines(game, filename))
	{
		free_map(game->map);
		ft_putendl_fd("Error\nCould not read map content.", 2);
		return (0);
	}
	return (validate_map(game, filename));
}
