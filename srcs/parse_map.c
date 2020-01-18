/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:59:06 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/18 15:31:34 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_begin(t_cub3d *tab, char *str, int fd)
{
	int	i;

	tab->nbrline = ft_nbr_map(tab, str, fd, &tab->lenline);
	i = -1;
	tab->carte = malloc(sizeof(int *) * (tab->lenline / 2 + 1));
	while (++i < (tab->lenline / 2 + 1))
		tab->carte[i] = malloc(sizeof(int) * tab->nbrline);
	fd = open(tab->name, O_RDONLY);
	i = -1;
	while (++i * 2 < tab->lenline)
	{
		if (ft_isdigit(str[i * 2]))
			tab->carte[i][0] = str[i * 2] - 48;
		else
			ft_error(tab, 3);
	}
	get_next_line(fd, &str);
	while (!(ft_isdigit(str[0])))
	{
		free(str);
		get_next_line(fd, &str);
	}
	free(str);
}

void	ft_position(t_cub3d *tab, char *str, int i, int j)
{
	if (tab->posx != 0 || tab->posy != 0)
		ft_error(tab, 3);
	tab->carte[tab->lenline / 2 - i][j] = 0;
	tab->posx = tab->lenline / 2 - i + 0.5;
	tab->posy = j + 0.5;
	if (str[i * 2] == 'N')
		tab->diry = -1;
	else if (str[i * 2] == 'S')
		tab->diry = 1;
	else if (str[i * 2] == 'E')
		tab->dirx = -1;
	else if (str[i * 2] == 'W')
		tab->dirx = 1;
}

int		*ft_handler(t_cub3d *tab, int *spr, char *str)
{
	if (str[tab->i * 2] == '2')
	{
		spr[tab->nbrspr] = tab->j * 100 + tab->lenline / 2 - tab->i;
		tab->nbrspr++;
		tab->carte[tab->lenline / 2 - tab->i][tab->j] = str[tab->i * 2] - 48;
	}
	else if (str[tab->i * 2] == '0' || str[tab->i * 2] == '1' ||
		str[tab->i * 2] == '3')
		tab->carte[tab->lenline / 2 - tab->i][tab->j] = str[tab->i * 2] - 48;
	else if (str[tab->i * 2] == 'N' || str[tab->i * 2] == 'S' ||
		str[tab->i * 2] == 'W' || str[tab->i * 2] == 'E')
		ft_position(tab, str, tab->i, tab->j);
	else
		ft_error(tab, 3);
	return (spr);
}

void	ft_parse_map(t_cub3d *tab, char *str, int fd)
{
	int spr[100];

	ft_begin(tab, str, fd);
	tab->j = 1;
	while (get_next_line(fd, &str))
	{
		tab->i = -1;
		while (++tab->i * 2 < tab->lenline)
			*spr = *ft_handler(tab, spr, str);
		tab->j++;
		free(str);
	}
	free(str);
	if (tab->dirx == 0 && tab->diry == 0)
		ft_error(tab, 4);
	if (tab->nbrspr)
	{
		tab->i = -1;
		if (!(tab->sprposi = malloc(sizeof(int) * tab->nbrspr)))
			exit(0);
		while (++tab->i < tab->nbrspr)
			tab->sprposi[tab->i] = spr[tab->i];
	}
}
