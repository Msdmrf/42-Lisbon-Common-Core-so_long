/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_compositor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:25:08 by migusant          #+#    #+#             */
/*   Updated: 2025/07/01 18:59:43 by migusant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_COMPOSITOR_H
# define XPM_COMPOSITOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h> 

# define MAX_LINE_LENGTH 1024
# define MAX_LINES 1000
# define MAX_COLORS 256

typedef struct s_xpm_file
{
	int		width;
	int		height;
	int		num_colors;
	int		chars_per_pixel;
	char	color_table[MAX_COLORS][64];
	char	pixel_data[MAX_LINES][MAX_LINE_LENGTH];
	char	var_name[256];
	int		data_lines;
}	t_xpm_file;

// Utility Functions
void	extract_var_name(const char *line, char *var_name);
char	get_color_char(const char *color_entry);
char	get_pixel_char(const char *line, int x, int chars_per_pixel);
void	set_pixel_char(char *line, int x, char c, int chars_per_pixel);
int		create_composite_directory(void);
void	generate_output_filename(const char *input_filename,
			char *output_filename);

// Parsing Functions
int		parse_xpm_file(const char *filename, t_xpm_file *xpm);
int		parse_xpm_header(FILE *file, t_xpm_file *xpm);
int		parse_color_table(FILE *file, t_xpm_file *xpm);
int		parse_pixel_data(FILE *file, t_xpm_file *xpm);

// Conflict Resolution
char	is_char_used(char candidate, t_xpm_file *foreground,
			t_xpm_file *background);
char	find_unused_char(t_xpm_file *foreground, t_xpm_file *background);
void	replace_char_in_pixel_data(t_xpm_file *xpm, char old_char,
			char new_char);
void	resolve_conflicts(t_xpm_file *foreground, t_xpm_file *background);

// Compositing Functions
void	merge_color_tables(t_xpm_file *foreground, t_xpm_file *background,
			t_xpm_file *result);
void	composite_pixels(t_xpm_file *foreground, t_xpm_file *background,
			t_xpm_file *result);
int		composite_single_xpm(t_xpm_file *foreground, t_xpm_file *background,
			t_xpm_file *result);

// Writing Functions
void	write_xpm_file(const char *filename, t_xpm_file *xpm);
void	write_xpm_header(FILE *file, t_xpm_file *xpm);
void	write_xpm_colors(FILE *file, t_xpm_file *xpm);
void	write_xpm_pixels(FILE *file, t_xpm_file *xpm);

// File Processing Functions
int		process_single_file(char *filename, t_xpm_file *background,
			int *processed);
int		process_files(int argc, char *argv[]);

// Main Program
void	print_usage(char *program_name);

#endif