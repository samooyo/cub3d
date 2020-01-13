/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:00:54 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/13 12:02:14 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_spr_cmp(t_cub3d *tab, int a, int b)
{
	int	diff;

	diff = sqrt(ft_square(a % 100 - tab->posx) + ft_square(a / 100 - tab->posy))
	- sqrt(ft_square(b % 100 - tab->posx) + ft_square(b / 100 - tab->posy));
	return (diff);
}

void	ft_sort_spr(t_cub3d *tab)
{
	int	i;
	int	trie;
	int	tpm;

	trie = 0;
	while (trie == 0)
	{
		trie = 1;
		i = -1;
		while (++i < tab->nbrspr - 1)
		{
			if (ft_spr_cmp(tab, tab->sprposi[i], tab->sprposi[i + 1]) < 0)
			{
				tpm = tab->sprposi[i];
				tab->sprposi[i] = tab->sprposi[i + 1];
				tab->sprposi[i + 1] = tpm;
				trie = 0;
			}
		}
	}
}

void	ft_sprite_bis(t_cub3d *tab, int i)
{
	tab->sprite->x = tab->sprposi[i] % 100 + 0.5;
	tab->sprite->y = tab->sprposi[i] / 100 + 0.5;
	tab->spr->spritex = tab->sprite->x - tab->posx;
	tab->spr->spritey = tab->sprite->y - tab->posy;
	tab->spr->invdet = 1.0 / (tab->planx * tab->diry - tab->dirx * tab->plany);
	tab->spr->transformx = tab->spr->invdet * (tab->diry * tab->spr->spritex
		- tab->dirx * tab->spr->spritey);
	tab->spr->transformy = tab->spr->invdet * (-tab->plany * tab->spr->spritex
		+ tab->planx * tab->spr->spritey);
	tab->spr->sprscreenx = (int)((tab->winx / 2) * (1 +
		tab->spr->transformx / tab->spr->transformy));
	tab->spr->h = abs((int)(tab->winy / (tab->spr->transformy)));
	tab->spr->drawstarty = -tab->spr->h / 2 + tab->winy / 2;
	if (tab->spr->drawstarty < 0)
		tab->spr->drawstarty = 0;
	tab->spr->drawendy = tab->spr->h / 2 + tab->winy / 2;
	if (tab->spr->drawendy >= tab->winy)
		tab->spr->drawendy = tab->winy;
	tab->spr->w = abs((int)(tab->winy / (tab->spr->transformy)));
	tab->spr->drawstartx = -tab->spr->w / 2 + tab->spr->sprscreenx;
	if (tab->spr->drawstartx < 0)
		tab->spr->drawstartx = 0;
	tab->spr->drawendx = tab->spr->w / 2 + tab->spr->sprscreenx;
	if (tab->spr->drawendx >= tab->winx)
		tab->spr->drawendx = tab->winx;
}

void	ft_sprite(t_cub3d *tab, int i)
{
	ft_sprite_bis(tab, i);
	tab->spr->stripe = tab->spr->drawstartx - 1;
	while (++tab->spr->stripe < tab->spr->drawendx)
	{
		tab->spr->texx = (int)(256 * (tab->spr->stripe - (-tab->spr->w
		/ 2 + tab->spr->sprscreenx)) * tab->sprite->width / tab->spr->w) / 256;
		if (tab->spr->transformy > 0 && tab->spr->stripe > 0 && tab->spr->stripe
		< tab->winx && tab->spr->transformy < tab->zbuf[tab->spr->stripe])
		{
			tab->spr->y = tab->spr->drawstarty - 1;
			while (++tab->spr->y < tab->spr->drawendy)
			{
				tab->spr->d = tab->spr->y * 256 - tab->winy * 128 +
					tab->spr->h * 128;
				tab->spr->texy = ((tab->spr->d * tab->sprite->width)
					/ tab->spr->h) / 256;
				tab->spr->color = mlx_get_pixel_clr(tab->sprite, tab->spr->texx,
				tab->spr->texy);
				if (tab->spr->color != 0x87ceff)
					mlx_put_pixel(tab, tab->spr->stripe, tab->spr->y,
						tab->spr->color);
			}
		}
	}
}
