/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:09:45 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/18 16:09:41 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialize_tab2(t_cub3d *tab)
{
	if (!(tab->no = malloc(sizeof(t_tex))))
		exit(0);
	tab->no->tex = NULL;
	if (!(tab->so = malloc(sizeof(t_tex))))
		exit(0);
	tab->so->tex = NULL;
	if (!(tab->we = malloc(sizeof(t_tex))))
		exit(0);
	tab->we->tex = NULL;
	if (!(tab->ea = malloc(sizeof(t_tex))))
		exit(0);
	tab->ea->tex = NULL;
	if (!(tab->floor = malloc(sizeof(t_tex))))
		exit(0);
	if (!(tab->ceilling = malloc(sizeof(t_tex))))
		exit(0);
	if (!(tab->sprite = malloc(sizeof(t_tex))))
		exit(0);
	tab->sprite->tex = NULL;
	if (!(tab->spr = malloc(sizeof(t_spr))))
		exit(0);
}

void	ft_switchs(t_cub3d *tab)
{
	tab->s_r = 0;
	tab->s_f = 0;
	tab->s_c = 0;
	tab->s_s = 0;
	tab->s_no = 0;
	tab->s_ea = 0;
	tab->s_we = 0;
	tab->s_so = 0;
	tab->save = 0;
}

void	ft_initialize_tab(t_cub3d *tab)
{
	tab->x = 0;
	tab->rotspeed = 0.06;
	tab->movspeed = 0.05;
	tab->posx = 0;
	tab->posy = 0;
	tab->dirx = 0;
	tab->diry = 0;
	tab->plany = 0;
	tab->planx = 0;
	tab->move_down = 0;
	tab->move_right = 0;
	tab->move_left = 0;
	tab->move_up = 0;
	tab->turn_right = 0;
	tab->turn_left = 0;
	tab->switchtex = 0;
	tab->nbrspr = 0;
	tab->winx = 0;
	tab->winy = 0;
	tab->floor_color = 0;
	tab->ceil_color = 0;
	ft_initialize_tab2(tab);
	ft_switchs(tab);
}

void	ft_check_cub(t_cub3d *tab, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (str[--i] != 'b')
		ft_error(tab, 6);
	if (str[--i] != 'u')
		ft_error(tab, 6);
	if (str[--i] != 'c')
		ft_error(tab, 6);
	if (str[--i] != '.')
		ft_error(tab, 6);
}

void	ini_tex(t_cub3d *tab)
{
	tab->floor->tex = mlx_xpm_file_to_image(tab->mlx, "textures/floor_new.xpm",
		&tab->floor->width, &tab->floor->height);
	tab->floor->datatex = mlx_get_data_addr(tab->floor->tex, &tab->floor->bpp,
		&tab->floor->sizeline, &tab->floor->endian);
	tab->ceilling->tex = mlx_xpm_file_to_image(tab->mlx, "textures/sky_new.xpm",
		&tab->ceilling->width, &tab->ceilling->height);
	tab->ceilling->datatex = mlx_get_data_addr(tab->ceilling->tex,
		&tab->ceilling->bpp, &tab->ceilling->sizeline, &tab->ceilling->endian);
}

int		main(int ac, char *av[])
{
	t_cub3d *tab;

	if (ac > 3 || ac < 2)
		ft_write();
	if (!(tab = malloc(sizeof(t_cub3d))))
		exit(0);
	ft_initialize_tab(tab);
	ft_check_cub(tab, av[1]);
	tab->mlx = mlx_init();
	ini_tex(tab);
	ft_parser(tab, av[1]);
	if (!(tab->win = mlx_new_window(tab->mlx, tab->winx,
		tab->winy, tab->name)))
		exit(0);
	if (ac == 3 && ft_strcmp(av[2], "-save") == 1)
		tab->save = 1;
	if (ac == 3 && ft_strcmp(av[2], "-save") != 1)
		ft_error(tab, 6);
	mlx_hook(tab->win, 2, (1L << 0), key_press, tab);
	mlx_hook(tab->win, 3, (1L << 1), key_release, tab);
	mlx_hook(tab->win, 17, 1L << 17, exit_game, tab);
	ft_ray(tab);
	mlx_loop_hook(tab->mlx, move, tab);
	mlx_loop(tab->mlx);
}
