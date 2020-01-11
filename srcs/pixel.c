/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:52:53 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/10 18:13:55 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mlx_get_pixel_clr(t_tex *tex, int x, int y)
{
	int				r;
	int				g;
	int				b;
	unsigned int	p;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->width)
		return (0);
	p = 4 * (x + (y * tex->width));
	r = tex->datatex[p + 2];
	g = tex->datatex[p + 1];
	b = tex->datatex[p];
	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
}

int		mlx_put_pixel(t_cub3d *tab, int x, int y, int clr)
{
	if (x < 0 || x >= tab->winx || y < 0 || y >= tab->winy)
		return (0);
	*((int *)&tab->img_ptr[(x * 4) + (y * (tab->winx * 4))]) = clr;
	return (0);
}

int		generate_clr(int r, int g, int b)
{
	int		color;
	char	*clr;

	clr = (char*)&color;
	clr[0] = b;
	clr[1] = g;
	clr[2] = r;
	return (color);
}
