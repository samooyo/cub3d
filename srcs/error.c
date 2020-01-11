/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:48:51 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/11 17:46:34 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!*s1 || !*s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (1);
	return (0);
}

void	ft_write(void)
{
	write(1, "Bad numer of arguments\n", 23);
	exit(0);
}

void	free_error(t_cub3d *tab)
{
	free(tab->no);
	free(tab->so);
	free(tab->ea);
	free(tab->we);
	free(tab->sprite);
	free(tab->ceilling);
	free(tab->floor);
	free(tab->spr);
}

void	free_game(t_cub3d *tab)
{
	free_error(tab);
	free(tab->zbuf);
	free(tab);
}

void	ft_error(t_cub3d *tab, int er)
{
	if (er == 0)
		write(2, MSG0, ft_strlen(MSG0));
	else if (er == 1)
		write(2, MSG1, ft_strlen(MSG1));
	else if (er == 2)
		write(2, MSG2, ft_strlen(MSG2));
	else if (er == 3)
		write(2, MSG3, ft_strlen(MSG3));
	else if (er == 4)
		write(2, MSG4, ft_strlen(MSG4));
	else if (er == 5)
		write(2, MSG5, ft_strlen(MSG5));
	else if (er == 6)
		write(2, MSG6, ft_strlen(MSG6));
	write(2, "\n", 1);
	free_error(tab);
	free(tab);
	exit(0);
}
