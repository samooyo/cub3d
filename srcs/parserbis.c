/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserbis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:55:40 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/18 16:16:35 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_load_sprite(t_cub3d *tab, char *str)
{
	int	i;

	i = 2;
	while (str[i] == ' ')
		i++;
	if (!(tab->sprite->tex = mlx_xpm_file_to_image(tab->mlx, str + i,
		&tab->sprite->width, &tab->sprite->height)))
		ft_error(tab, 5);
	tab->sprite->datatex = mlx_get_data_addr(tab->sprite->tex,
		&tab->sprite->bpp, &tab->sprite->sizeline, &tab->sprite->endian);
	tab->s_s = 1;
}

void	ft_color_check(t_cub3d *tab, char *str, int floor)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	tab->clr[j++] = atoi(str + 1);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] && ft_isdigit(str[++i]))
		tab->clr[j++] = atoi(str + i);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] && ft_isdigit(str[++i]))
		tab->clr[j] = atoi(str + i);
	if (j != 2)
		ft_error(tab, 1);
	j = 3;
	while (--j >= 0)
		if (tab->clr[j] > 255 || tab->clr[j] < 0)
			ft_error(tab, 1);
	if (floor == 1)
		tab->floor_color = generate_clr(tab->clr[0], tab->clr[1], tab->clr[2]);
	else
		tab->ceil_color = generate_clr(tab->clr[0], tab->clr[1], tab->clr[2]);
}

void	ft_parse_tex_bis(t_cub3d *tab, char *str, int i)
{
	if (str[0] == 'W' && str[1] == 'E' && !tab->s_we)
	{
		while (str[i] == ' ')
			i++;
		if (!(tab->we->tex = mlx_xpm_file_to_image(tab->mlx, str + i,
			&tab->we->width, &tab->we->height)))
			ft_error(tab, 2);
		tab->we->datatex = mlx_get_data_addr(tab->we->tex, &tab->we->bpp,
			&tab->we->sizeline, &tab->we->endian);
		tab->s_we = 1;
	}
	else if (str[0] == 'E' && str[1] == 'A' && !tab->s_ea)
	{
		while (str[i] == ' ')
			i++;
		if (!(tab->ea->tex = mlx_xpm_file_to_image(tab->mlx, str + i,
			&tab->ea->width, &tab->ea->height)))
			ft_error(tab, 2);
		tab->ea->datatex = mlx_get_data_addr(tab->ea->tex, &tab->ea->bpp,
			&tab->ea->sizeline, &tab->ea->endian);
		tab->s_ea = 1;
	}
	else
		ft_error(tab, 2);
}

void	ft_parse_tex(t_cub3d *tab, char *str)
{
	int	i;

	i = 2;
	if (str[0] == 'N' && str[1] == 'O' && !tab->s_no)
	{
		while (str[i] == ' ')
			i++;
		if (!(tab->no->tex = mlx_xpm_file_to_image(tab->mlx, str + i,
			&tab->no->width, &tab->no->height)))
			ft_error(tab, 2);
		tab->no->datatex = mlx_get_data_addr(tab->no->tex, &tab->no->bpp,
			&tab->no->sizeline, &tab->no->endian);
		tab->s_no = 1;
	}
	else if (str[0] == 'S' && str[1] == 'O' && !tab->s_so)
	{
		while (str[i] == ' ')
			i++;
		if (!(tab->so->tex = mlx_xpm_file_to_image(tab->mlx, str + i,
			&tab->so->width, &tab->so->height)))
			ft_error(tab, 2);
		tab->so->datatex = mlx_get_data_addr(tab->so->tex, &tab->so->bpp,
			&tab->so->sizeline, &tab->so->endian);
		tab->s_so = 1;
	}
	else
		ft_parse_tex_bis(tab, str, i);
}

void	ft_res(t_cub3d *tab, char *str)
{
	int	i;

	i = 0;
	tab->winx = atoi(str + 1);
	while (str[i] == 'R' || str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		tab->winy = atoi(str + i);
	if (tab->winx < 1 || tab->winy < 1)
		ft_error(tab, 0);
	if (tab->winx > 2560)
		tab->winx = 2560;
	if (tab->winx > 1440)
		tab->winy = 1440;
	tab->s_r = 1;
}
