/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 10:31:41 by dperez-p          #+#    #+#             */
/*   Updated: 2026/05/15 15:15:11 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Return error msg */
int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd(RED "Error\n", 2);
	if (detail)
	{
		ft_putstr_fd(detail, 2);
		ft_putstr_fd(": ", 2);
	}
	if (str)
	{
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n" RESET, 2);
	return (code);
}
