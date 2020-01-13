/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:38:44 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/13 11:20:13 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bis(t_cub3d *tab)
{
	if (tab->raydirx < 0)
	{
		tab->stepx = -1;
		tab->sidedistx = (tab->rayposx - tab->mapx) * tab->deltadistx;
	}
	else
	{
		tab->stepx = 1;
		tab->sidedistx = (tab->mapx + 1.0 - tab->rayposx) * tab->deltadistx;
	}
	if (tab->raydiry < 0)
	{
		tab->stepy = -1;
		tab->sidedisty = (tab->rayposy - tab->mapy) * tab->deltadisty;
	}
	else
	{
		tab->stepy = 1;
		tab->sidedisty = (tab->mapy + 1.0 - tab->rayposy) * tab->deltadisty;
	}
}

void	ft_ray_bis(t_cub3d *tab)
{
	tab->camerax = 2 * tab->x / (double)(tab->winx) - 1;
	tab->rayposx = tab->posx;
	tab->rayposy = tab->posy;
	tab->raydirx = tab->dirx + tab->planx * tab->camerax;
	tab->raydiry = tab->diry + tab->plany * tab->camerax;
	tab->mapx = (int)tab->rayposx;
	tab->mapy = (int)tab->rayposy;
	tab->deltadisty = fabs(1 / tab->raydiry);
	tab->deltadistx = fabs(1 / tab->raydirx);
	bis(tab);
}

void	ft_hit_bis(t_cub3d *tab)
{
	if (tab->side == 0)
		tab->perswdis = (tab->mapx - tab->rayposx +
			(1 - tab->stepx) / 2) / tab->raydirx;
	else
		tab->perswdis = (tab->mapy - tab->rayposy +
			(1 - tab->stepy) / 2) / tab->raydiry;
	tab->zbuf[tab->x] = tab->perswdis;
}

void	ft_hit(t_cub3d *tab)
{
	tab->hit = 0;
	while (tab->hit == 0)
	{
		if (tab->sidedistx < tab->sidedisty)
		{
			tab->sidedistx += tab->deltadistx;
			tab->mapx += tab->stepx;
			tab->side = 0;
		}
		else
		{
			tab->sidedisty += tab->deltadisty;
			tab->mapy += tab->stepy;
			tab->side = 1;
		}
		if (tab->mapx < 0)
			tab->mapx = 0;
		if (tab->carte[tab->mapx][tab->mapy] == 1 ||
			tab->carte[tab->mapx][tab->mapy] == 3)
			tab->hit = 1;
	}
	ft_hit_bis(tab);
}

void	ft_ray(t_cub3d *tab)
{
	int i;

	if (!(tab->img = mlx_new_image(tab->mlx, tab->winx, tab->winy)))
		exit(0);
	tab->img_ptr = mlx_get_data_addr(tab->img,
		&tab->bitspp, &tab->sizeline, &tab->endian);
	tab->x = 0;
	while (tab->x < tab->winx)
	{
		ft_ray_bis(tab);
		ft_hit(tab);
		ft_draw(tab);
		if (tab->switchtex)
			floor_direction(tab);
		tab->x++;
	}
	if (tab->nbrspr > 1)
		ft_sort_spr(tab);
	i = -1;
	while (++i < tab->nbrspr)
		ft_sprite(tab, i);
	if (tab->save)
		save_bmp(tab);
	mlx_put_image_to_window(tab->mlx, tab->win, tab->img, 0, 0);
	mlx_destroy_image(tab->mlx, tab->img);
}
