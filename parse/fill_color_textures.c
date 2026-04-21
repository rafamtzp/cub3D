/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:54:21 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/21 15:26:10 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Count the number of tabs in a matrix */
static int	count_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

/* Check if are only digits skipping spaces */
static int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (str[i] == '\0');
}

/* Parse the current RGB */
static int	parse_single_rgb(char *str)
{
	int	value;

	if (!is_only_digits(str))
		return (-1);
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

/* Set and return the combine of RGB colours */
static int	set_rgb_colours(char	*line)
{
	char	**tmp;
	int		rgb[3];
	int		i;

	tmp = ft_split(line, ',');
	if (!tmp)
		return (-1);
	if (count_tab(tmp) != 3)
	{
		ft_free_matrix((void **)tmp);
		return (-1);
	}
	i = -1;
	while (++i < 3)
	{
		rgb[i] = parse_single_rgb(tmp[i]);
		if (rgb[i] == -1)
		{
			ft_free_matrix((void **)tmp);
			return (-1);
		}
	}
	ft_free_matrix((void **)tmp);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/* Check if the color is duplicate and if not parse the info */
int	fill_color_textures(t_texinfo *textures, char *line, int j)
{
	if (line[j] == 'F')
	{
		if (textures->floor != -1)
			return (err_msg("Floor", "Duplicate color", FAILURE));
		textures->floor = set_rgb_colours(&line[j + 1]);
		if (textures->floor == -1)
			return (err_msg("Floor", "Invalid color format", FAILURE));
	}
	else if (line[j] == 'C')
	{
		if (textures->ceiling != -1)
			return (err_msg("Ceiling", "Duplicate color", FAILURE));
		textures->ceiling = set_rgb_colours(&line[j + 1]);
		if (textures->ceiling == -1)
			return (err_msg("Ceiling", "Invalid color format", FAILURE));
	}
	return (SUCCESS);
}
