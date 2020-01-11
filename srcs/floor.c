/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:16:48 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/11 17:23:26 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_cub3d *tab)
{
	int		y;

	y = tab->drawend + 1;
	while (y < tab->winy)
	{
		tab->currentdist = (double)tab->winy /
			(2 * (double)y - (double)tab->winy);
		tab->floorxx = tab->currentdist / tab->perswdis * tab->floorx +
			(1 - (tab->currentdist / tab->perswdis)) * tab->posx;
		tab->flooryy = tab->currentdist / tab->perswdis * tab->floory +
			(1 - (tab->currentdist / tab->perswdis)) * tab->posy;
		tab->floortexx = (int)(tab->floorxx * tab->floor->height)
			% tab->floor->height;
		tab->floortexy = (int)(tab->flooryy * tab->floor->height)
			% tab->floor->height;
		mlx_put_pixel(tab, tab->x, y, mlx_get_pixel_clr(tab->floor,
			tab->floortexx, tab->floortexy));
		tab->floortexx = (int)(tab->floorxx * tab->ceilling->height)
			% tab->ceilling->height;
		tab->floortexy = (int)(tab->flooryy * tab->ceilling->height)
			% tab->ceilling->height;
		mlx_put_pixel(tab, tab->x, tab->winy - y, mlx_get_pixel_clr(
			tab->ceilling, tab->floortexx, tab->floortexy));
		y++;
	}
}

void	floor_direction(t_cub3d *tab)
{
	if (tab->side == 0 && tab->raydirx > 0)
	{
		tab->floorx = tab->mapx;
		tab->floory = tab->mapy + tab->wallx;
	}
	else if (tab->side == 0 && tab->raydirx < 0)
	{
		tab->floorx = tab->mapx + 1;
		tab->floory = tab->mapy + tab->wallx;
	}
	else if (tab->side == 1 && tab->raydiry > 0)
	{
		tab->floorx = tab->mapx + tab->wallx;
		tab->floory = tab->mapy;
	}
	else
	{
		tab->floorx = tab->mapx + tab->wallx;
		tab->floory = tab->mapy + 1;
	}
	if (tab->drawend < 0)
		tab->drawend = tab->winy;
	draw_floor(tab);
}
