/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:34:27 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/11 17:05:18 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_nbr_map(t_cub3d *tab, char *str, int fd, int *lenline)
{
	int nbrline;

	nbrline = 1;
	*lenline = strlen(str);
	while (get_next_line(fd, &str))
	{
		if (str[0] == '1')
		{
			if (*lenline == ft_strlen(str))
				nbrline++;
			else
				ft_error(tab, 3);
		}
		else
			ft_error(tab, 3);
	}
	close(fd);
	return (nbrline);
}

void	ft_parse_bis(t_cub3d *tab, char *str)
{
	if (str[0] == 'R' && str[1] == ' ')
		ft_res(tab, str);
	else if (str[0] == 'F' && str[1] == ' ')
		ft_color_check(tab, str, 1);
	else if (str[0] == 'C' && str[1] == ' ')
		ft_color_check(tab, str, 0);
	else if (str[0] == 'N' || (str[0] == 'S' && str[1] == 'O')
		|| str[0] == 'W' || str[0] == 'E')
		ft_parse_tex(tab, str);
	else if (str[0] == 'S' && str[1] == ' ')
		ft_load_sprite(tab, str);
	else
		ft_error(tab, 4);
}

void	ft_check(t_cub3d *tab)
{
	if (tab->no->tex == NULL || tab->so->tex == NULL || tab->we->tex
		== NULL || tab->ea->tex == NULL)
		ft_error(tab, 2);
	if (tab->winx == 0 || tab->winy == 0)
		ft_error(tab, 0);
	if (tab->floor_color == 0 || tab->ceil_color == 0)
		ft_error(tab, 1);
	if (tab->sprite->tex == NULL)
		ft_error(tab, 5);
}

void	ft_parser(t_cub3d *tab, char *name)
{
	int		fd;
	char	*str;
	char	c;

	tab->name = name;
	if ((fd = open(tab->name, O_RDONLY)) == -1)
		ft_error(tab, 6);
	while (get_next_line(fd, &str))
	{
		c = str[0];
		if (c == 'R' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
			|| c == 'F' || c == 'C')
			ft_parse_bis(tab, str);
		else if (c == '0' || c == '1')
			ft_parse_map(tab, str, fd);
		else if (c == 0)
			;
		else
			ft_error(tab, 4);
	}
	tab->plany = 0.57735 * -tab->dirx;
	tab->planx = 0.57735 * tab->diry;
	tab->zbuf = malloc(sizeof(double) * tab->winx);
	close(fd);
	ft_check(tab);
}
