/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_compositor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:27:23 by migusant          #+#    #+#             */
/*   Updated: 2025/07/01 18:59:41 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm_compositor.h"

// Utility Functions
void	extract_var_name(const char *line, char *var_name)
{
	char	*start;
	char	*end;
	int		len;

	start = strstr(line, "static char *");
	if (start)
	{
		start += strlen("static char *");
		end = strstr(start, "[]");
		if (end)
		{
			len = end - start;
			strncpy(var_name, start, len);
			var_name[len] = '\0';
		}
		else
			strcpy(var_name, "unknown");
	}
	else
		strcpy(var_name, "unknown");
}

char	get_color_char(const char *color_entry)
{
	return (color_entry[1]);
}

char	get_pixel_char(const char *line, int x, int chars_per_pixel)
{
	int	start_pos;

	start_pos = 1 + (x * chars_per_pixel);
	return (line[start_pos]);
}

void	set_pixel_char(char *line, int x, char c, int chars_per_pixel)
{
	int	start_pos;

	start_pos = 1 + (x * chars_per_pixel);
	line[start_pos] = c;
}

int	create_composite_directory(void)
{
	struct stat	st;

	st = (struct stat){0};
	if (stat("composite", &st) == -1)
	{
		if (mkdir("composite", 0755) != 0)
		{
			printf("Error: Could not create 'composite' directory!\n");
			return (0);
		}
		printf("Created 'composite' directory!\n");
	}
	return (1);
}

void	generate_output_filename(const char *input_filename,
	char *output_filename)
{
	const char	*base_name;

	base_name = strrchr(input_filename, '/');
	if (base_name)
		base_name = base_name + 1;
	else
		base_name = input_filename;
	strcpy(output_filename, "composite/");
	strcat(output_filename, base_name);
}

// Parsing Functions
int	parse_xpm_header(FILE *file, t_xpm_file *xpm)
{
	char	line[MAX_LINE_LENGTH];

	if (!fgets(line, sizeof(line), file))
		return (0);
	extract_var_name(line, xpm->var_name);
	if (!fgets(line, sizeof(line), file))
		return (0);
	sscanf(line, "\"%d %d %d %d", &xpm->width, &xpm->height,
		&xpm->num_colors, &xpm->chars_per_pixel);
	return (1);
}

int	parse_color_table(FILE *file, t_xpm_file *xpm)
{
	char	line[MAX_LINE_LENGTH];
	int		i;

	i = 0;
	while (i < xpm->num_colors)
	{
		if (!fgets(line, sizeof(line), file))
			return (0);
		strcpy(xpm->color_table[i], line);
		i++;
	}
	return (1);
}

int	parse_pixel_data(FILE *file, t_xpm_file *xpm)
{
	char	line[MAX_LINE_LENGTH];

	xpm->data_lines = 0;
	while (fgets(line, sizeof(line), file) && xpm->data_lines < xpm->height)
	{
		if (line[0] != '"')
			continue ;
		strcpy(xpm->pixel_data[xpm->data_lines], line);
		xpm->data_lines++;
	}
	return (1);
}

int	parse_xpm_file(const char *filename, t_xpm_file *xpm)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("Error: Cannot open file %s\n", filename);
		return (0);
	}
	if (!parse_xpm_header(file, xpm) || !parse_color_table(file, xpm)
		|| !parse_pixel_data(file, xpm))
	{
		fclose(file);
		return (0);
	}
	fclose(file);
	return (1);
}

// Conflict Resolution
char	is_char_used(char candidate, t_xpm_file *foreground,
		t_xpm_file *background)
{
	int	j;

	j = 0;
	while (j < foreground->num_colors)
	{
		if (get_color_char(foreground->color_table[j]) == candidate)
			return (1);
		j++;
	}
	j = 0;
	while (j < background->num_colors)
	{
		if (get_color_char(background->color_table[j]) == candidate)
			return (1);
		j++;
	}
	return (0);
}

char	find_unused_char(t_xpm_file *foreground, t_xpm_file *background)
{
	const char	candidates[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklm"
		"nopqrstuvwxyz0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	int			i;
	char		candidate;

	i = 0;
	while (candidates[i] != '\0')
	{
		candidate = candidates[i];
		if (!is_char_used(candidate, foreground, background))
			return (candidate);
		i++;
	}
	printf("Warning: Could not find unused character for remapping!\n");
	return ('?');
}

void	replace_char_in_pixel_data(t_xpm_file *xpm, char old_char,
		char new_char)
{
	int	y;
	int	x;

	y = 0;
	while (y < xpm->data_lines)
	{
		x = 1;
		while (x < (int)strlen(xpm->pixel_data[y]))
		{
			if (xpm->pixel_data[y][x] == old_char)
				xpm->pixel_data[y][x] = new_char;
			x++;
		}
		y++;
	}
}

void	resolve_conflicts(t_xpm_file *foreground, t_xpm_file *background)
{
	int		i;
	int		j;
	char	fg_char;
	char	bg_char;
	char	new_char;

	i = -1;
	while (++i < foreground->num_colors)
	{
		fg_char = get_color_char(foreground->color_table[i]);
		j = -1;
		while (++j < background->num_colors)
		{
			bg_char = get_color_char(background->color_table[j]);
			if (fg_char == bg_char)
			{
				new_char = find_unused_char(foreground, background);
				printf("Remapping '%c' to '%c' in %s\n", fg_char, new_char,
					foreground->var_name);
				foreground->color_table[i][1] = new_char;
				replace_char_in_pixel_data(foreground, fg_char, new_char);
				break ;
			}
		}
	}
}

// Compositing Functions
void	merge_color_tables(t_xpm_file *foreground, t_xpm_file *background,
		t_xpm_file *result)
{
	int	total_colors;
	int	i;

	total_colors = 0;
	i = 0;
	while (i < foreground->num_colors)
	{
		strcpy(result->color_table[total_colors], foreground->color_table[i]);
		total_colors++;
		i++;
	}
	i = 0;
	while (i < background->num_colors)
	{
		strcpy(result->color_table[total_colors], background->color_table[i]);
		total_colors++;
		i++;
	}
	result->num_colors = total_colors;
}

void	composite_pixels(t_xpm_file *foreground, t_xpm_file *background,
		t_xpm_file *result)
{
	int		y;
	int		x;
	char	fg_char;
	char	bg_char;

	y = -1;
	while (++y < result->data_lines)
	{
		strcpy(result->pixel_data[y], foreground->pixel_data[y]);
		x = -1;
		while (++x < result->width)
		{
			fg_char = get_pixel_char(foreground->pixel_data[y], x,
					foreground->chars_per_pixel);
			if (fg_char == ' ')
			{
				bg_char = get_pixel_char(background->pixel_data[y], x,
						background->chars_per_pixel);
				set_pixel_char(result->pixel_data[y], x, bg_char,
					result->chars_per_pixel);
			}
		}
	}
}

int	composite_single_xpm(t_xpm_file *foreground, t_xpm_file *background,
	t_xpm_file *result)
{
	if (foreground->width != background->width
		|| foreground->height != background->height)
	{
		printf("Error: Dimensions don't match for %s!\n",
			foreground->var_name);
		return (0);
	}
	resolve_conflicts(foreground, background);
	result->width = foreground->width;
	result->height = foreground->height;
	result->chars_per_pixel = 1;
	result->data_lines = foreground->data_lines;
	strcpy(result->var_name, foreground->var_name);
	merge_color_tables(foreground, background, result);
	composite_pixels(foreground, background, result);
	return (1);
}

// Writing Functions
void	write_xpm_header(FILE *file, t_xpm_file *xpm)
{
	fprintf(file, "static char *%s[] = {\n", xpm->var_name);
	fprintf(file, "\"%d %d %d %d \",\n", xpm->width, xpm->height,
		xpm->num_colors, xpm->chars_per_pixel);
}

void	write_xpm_colors(FILE *file, t_xpm_file *xpm)
{
	int	i;

	i = 0;
	while (i < xpm->num_colors)
	{
		fprintf(file, "%s", xpm->color_table[i]);
		i++;
	}
}

void	write_xpm_pixels(FILE *file, t_xpm_file *xpm)
{
	int		i;
	char	*comma;

	i = 0;
	while (i < xpm->data_lines)
	{
		if (i == xpm->data_lines - 1)
		{
			comma = strrchr(xpm->pixel_data[i], ',');
			if (comma)
				*comma = '\0';
		}
		fprintf(file, "%s", xpm->pixel_data[i]);
		i++;
	}
}

void	write_xpm_file(const char *filename, t_xpm_file *xpm)
{
	FILE	*file;

	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Cannot create output file %s\n", filename);
		return ;
	}
	write_xpm_header(file, xpm);
	write_xpm_colors(file, xpm);
	write_xpm_pixels(file, xpm);
	fprintf(file, "};\n");
	fclose(file);
}

// File Processing Functions
int	process_single_file(char *filename, t_xpm_file *background, int *processed)
{
	t_xpm_file	foreground;
	t_xpm_file	result;
	char		output_filename[512];

	printf("Processing: %s\n", filename);
	if (!parse_xpm_file(filename, &foreground))
	{
		printf("Warning: Failed to load %s, skipping...\n", filename);
		return (0);
	}
	if (composite_single_xpm(&foreground, background, &result))
	{
		generate_output_filename(filename, output_filename);
		printf("Writing: %s\n\n", output_filename);
		write_xpm_file(output_filename, &result);
		(*processed)++;
		return (1);
	}
	else
	{
		printf("Error compositing %s\n", foreground.var_name);
		return (0);
	}
}

int	process_files(int argc, char *argv[])
{
	t_xpm_file	background;
	int			processed;
	int			i;

	if (!parse_xpm_file(argv[1], &background))
	{
		printf("Error reading background file\n");
		return (1);
	}
	printf("\nCompositing files...\n");
	processed = 0;
	i = 0;
	while (i < argc - 2)
	{
		process_single_file(argv[2 + i], &background, &processed);
		i++;
	}
	printf("\nComposition complete! Processed %d files.\n", processed);
	return (0);
}

// Main Program
void	print_usage(char *program_name)
{
	printf("Usage: %s <background.xpm> <foreground1.xpm> ", program_name);
	printf("[foreground2.xpm] ...\n");
	printf("This program composites foreground xpm files onto a ");
	printf("background xpm file.\n");
	printf("Only SPACES in foregrounds are treated as transparent.\n");
	printf("Character conflicts with background are automatically resolved.\n");
	printf("Output files are named with '_comp' suffix.\n");
}

int	main(int argc, char *argv[])
{
	if (argc < 3)
	{
		print_usage(argv[0]);
		return (1);
	}
	if (!create_composite_directory())
		return (1);
	printf("xpm Compositor\n");
	printf("Background: %s\n", argv[1]);
	printf("Foreground files: %d\n", argc - 2);
	return (process_files(argc, argv));
}
