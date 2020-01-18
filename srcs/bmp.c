/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:39:12 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/18 15:49:01 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;
typedef unsigned short		t_ushort;
typedef unsigned long		t_ulong;

void	fill_headers(t_bmp *bmp, int width, int height)
{
	int len;
	int mod;

	len = height * width * 3;
	mod = width % 4;
	if (mod > 0)
		len += width * mod;
	bmp->padding = mod;
	bmp->signature[0] = 'B';
	bmp->signature[1] = 'M';
	bmp->totalsize = len + 54;
	bmp->offset = 54;
	bmp->bm_headersize = 40;
	bmp->imagesize = len;
	bmp->hres = 3780;
	bmp->vres = 3780;
	bmp->width = width;
	bmp->height = height;
	bmp->planes_number = 1;
	bmp->ncolors = 0;
	bmp->nimpcolors = 0;
	bmp->bpp = 24;
	bmp->compression_type = 0;
}

void	fill_header(char **img, t_cub3d *tab)
{
	t_uint len;

	len = tab->winx * tab->winy * 3;
	*(t_ushort *)*img = *(const t_uint *)(t_ulong)"BM";
	*(t_uint *)(*img + 2) = (len + 122);
	*(t_uint *)(*img + 6) = 0;
	*(t_uchar *)(*img + 10) = 122;
	*(t_uint *)(*img + 14) = 108;
	*(t_uint *)(*img + 18) = tab->winx;
	*(t_uint *)(*img + 22) = tab->winy;
	*(t_ushort *)(*img + 26) = 1;
	*(t_ushort *)(*img + 28) = 24;
	*(t_uint *)(*img + 30) = 0;
	*(t_uint *)(*img + 34) = len;
	*(t_uint *)(*img + 38) = 3780;
	*(t_uint *)(*img + 42) = 3780;
	*(int *)(*img + 46) = 0;
	*(int *)(*img + 50) = 0;
}

void	fill_bmp(char **img, t_cub3d *tab)
{
	int i;
	int j;
	int x;
	int y;

	j = 122;
	y = tab->winy;
	while (--y >= 0)
	{
		x = -1;
		while (++x < tab->winx)
		{
			i = (x * (tab->bitspp / 8)) + (y * tab->sizeline);
			*(*img + j++) = *(tab->img_ptr + i++);
			*(*img + j++) = *(tab->img_ptr + i++);
			*(*img + j++) = *(tab->img_ptr + i);
		}
	}
}

void	save_bmp(t_cub3d *tab)
{
	char	*img;
	int		fd;
	t_uint	len;
	t_uint	i;

	i = -1;
	len = tab->winx * tab->winy * 3;
	if (!(img = malloc((len + 122))))
		exit(0);
	while (++i < len + 122)
		img[i] = 0;
	fill_header(&img, tab);
	fill_bmp(&img, tab);
	if ((fd = open("screenShot.bmp", O_CREAT | O_TRUNC | O_RDWR, 0777)) <= 0)
		exit(0);
	write(fd, img, (len + 122));
	close(fd);
	exit_game(tab);
}
