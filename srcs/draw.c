/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:47:03 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/10 18:35:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sky(t_cub3d *tab)
{
	if (tab->drawstart > 0)
	{
		tab->y = -1;
		if (tab->x < tab->winx && tab->y < tab->winy)
			while (++tab->y < tab->drawstart)
				mlx_put_pixel(tab, tab->x, tab->y, tab->ceil_color);
	}
}

void	ft_floor(t_cub3d *tab)
{
	if (tab->drawend > 0)
	{
		tab->y = tab->drawend - 1;
		if (tab->x < tab->winx && tab->y < tab->winy)
			while (++tab->y < tab->winy)
				mlx_put_pixel(tab, tab->x, tab->y, tab->floor_color);
	}
}

void	ft_draw(t_cub3d *tab)
{
	tab->hauteurligne = (int)(tab->winy / tab->perswdis);
	tab->drawstart = -tab->hauteurligne / 2 + tab->winy / 2;
	tab->drawend = tab->hauteurligne / 2 + tab->winy / 2;
	if (tab->side == 0)
		tab->wallx = tab->posy + tab->perswdis * tab->raydiry;
	else
		tab->wallx = tab->posx + tab->perswdis * tab->raydirx;
	tab->wallx -= floor((tab->wallx));
	if (tab->drawstart < 0)
		tab->drawstart = 0;
	if (tab->drawend > tab->winy)
		tab->drawend = tab->winy;
	tab->y = tab->drawstart;
	ft_wall_tex(tab);
	if (!tab->switchtex)
	{
		ft_sky(tab);
		ft_floor(tab);
	}
}
