/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:16:28 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/10 18:37:10 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_wall_tex4(t_cub3d *tab)
{
	tab->texx = (int)(tab->wallx * (double)tab->so->width);
	if (tab->side == 0 && tab->raydirx > 0)
		tab->texx = tab->so->width - tab->texx - 1;
	if (tab->side == 1 && tab->raydiry < 0)
		tab->texx = tab->so->width - tab->texx - 1;
	tab->y = tab->drawstart;
	while (tab->y < tab->drawend)
	{
		tab->d = tab->y * 256 - tab->winy
			* 128 + tab->hauteurligne * 128;
		tab->texy = ((tab->d * tab->so->width) / tab->hauteurligne) / 256;
		mlx_put_pixel(tab, tab->x, tab->y,
			mlx_get_pixel_clr(tab->so, tab->texx, tab->texy));
		tab->y++;
	}
}

void	ft_wall_tex3(t_cub3d *tab)
{
	tab->texx = (int)(tab->wallx * (double)tab->no->width);
	if (tab->side == 0 && tab->raydirx > 0)
		tab->texx = tab->no->width - tab->texx - 1;
	if (tab->side == 1 && tab->raydiry < 0)
		tab->texx = tab->no->width - tab->texx - 1;
	tab->y = tab->drawstart;
	while (tab->y < tab->drawend)
	{
		tab->d = tab->y * 256 - tab->winy * 128 + tab->hauteurligne * 128;
		tab->texy = ((tab->d * tab->no->width) / tab->hauteurligne) / 256;
		mlx_put_pixel(tab, tab->x, tab->y,
			mlx_get_pixel_clr(tab->no, tab->texx, tab->texy));
		tab->y++;
	}
}

void	ft_wall_tex2(t_cub3d *tab)
{
	if (tab->side == 0 && tab->raydirx < 0)
	{
		tab->texx = (int)(tab->wallx * (double)(tab->ea->width));
		if (tab->side == 0 && tab->raydirx > 0)
			tab->texx = tab->ea->width - tab->texx - 1;
		if (tab->side == 1 && tab->raydiry < 0)
			tab->texx = tab->ea->width - tab->texx - 1;
		while (tab->y < tab->winy && tab->y < tab->drawend)
		{
			tab->d = tab->y * 256 - tab->winy * 128 + tab->hauteurligne * 128;
			tab->texy = ((tab->d * tab->ea->width) / tab->hauteurligne) / 256;
			mlx_put_pixel(tab, tab->x, tab->y,
				mlx_get_pixel_clr(tab->ea, tab->texx, tab->texy));
			tab->y++;
		}
	}
	else
		ft_wall_tex3(tab);
}

void	ft_wall_tex(t_cub3d *tab)
{
	if (tab->side == 0 && tab->raydirx > 0)
	{
		tab->texx = (int)(tab->wallx * (double)(tab->we->width));
		if (tab->side == 0 && tab->raydirx > 0)
			tab->texx = tab->we->width - tab->texx - 1;
		if (tab->side == 1 && tab->raydiry < 0)
			tab->texx = tab->we->width - tab->texx - 1;
		while (tab->y < tab->winy && tab->y < tab->drawend)
		{
			tab->d = tab->y * 256 - tab->winy * 128 + tab->hauteurligne * 128;
			tab->texy = ((tab->d * tab->we->width)
				/ tab->hauteurligne) / 256;
			mlx_put_pixel(tab, tab->x, tab->y,
				mlx_get_pixel_clr(tab->we, tab->texx, tab->texy));
			tab->y++;
		}
	}
	else if (tab->side == 1 && tab->raydiry > 0)
		ft_wall_tex4(tab);
	else
		ft_wall_tex2(tab);
}
