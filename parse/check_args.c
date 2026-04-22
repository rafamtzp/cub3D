/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:27:32 by dperez-p          #+#    #+#             */
/*   Updated: 2026/04/22 17:30:58 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Check if the path is a directory */
static bool	is_dir(char *ag)
{
	int		fd;

	fd = open(ag, O_DIRECTORY | O_RDONLY);
	if (fd == -1)
	{
		return (false);
	}
	close(fd);
	return (true);
}

/* Check if the extension of a file is .cub */
static bool	is_cubed_file(char *ag)
{
	size_t	len;

	len = ft_strlen(ag);
	if (len < 5)
		return (false);
	if (ft_strncmp(ag + (len - 4), ".cub", 4) == 0)
		return (true);
	return (false);
}

/* Check if the extension of a file is .xpm */
static bool	is_xpm_file(char *ag)
{
	size_t	len;

	len = ft_strlen(ag);
	if (len < 5)
		return (false);
	if (ft_strncmp(ag + (len - 4), ".xpm", 4) == 0)
		return (true);
	return (false);
}

/* Check if a file is valid (not a directory, exists,
	and has the right extension) */
int	check_file(char	*ag, bool cub)
{
	int	fd;

	if (is_dir(ag))
		return (err_msg(ag, "Is a directory", 1));
	fd = open(ag, O_RDONLY);
	if (fd == -1)
		return (err_msg(ag, strerror(errno), 1));
	close(fd);
	if (cub && !is_cubed_file(ag))
		return (err_msg(ag, "Not a .cub file", 1));
	if (!cub && !is_xpm_file(ag))
		return (err_msg(ag, "Not a .xmp file", 1));
	return (SUCCESS);
}
