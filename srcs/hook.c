/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 10:51:17 by tglandai          #+#    #+#             */
/*   Updated: 2020/01/13 10:33:55 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_cub3d *tab)
{
	if (keycode == 13 || keycode == 126)
		tab->move_up = 1;
	else if (keycode == 1 || keycode == 125)
		tab->move_down = 1;
	else if (keycode == 124)
		tab->turn_right = 1;
	else if (keycode == 123)
		tab->turn_left = 1;
	else if (keycode == 0)
		tab->move_left = 1;
	else if (keycode == 2)
		tab->move_right = 1;
	else if (keycode == 257 || keycode == 258)
		tab->movspeed = 0.07 + 0.03 * tab->switchtex;
	else if (keycode == 17)
	{
		if (tab->switchtex)
			tab->switchtex = 0;
		else
			tab->switchtex = 1;
	}
	else if (keycode == 53)
		exit_game(tab);
	return (0);
}

int		key_release(int keycode, t_cub3d *tab)
{
	if (keycode == 13 || keycode == 126)
		tab->move_up = 0;
	else if (keycode == 1 || keycode == 125)
		tab->move_down = 0;
	else if (keycode == 124)
		tab->turn_right = 0;
	else if (keycode == 123)
		tab->turn_left = 0;
	else if (keycode == 0)
		tab->move_left = 0;
	else if (keycode == 2)
		tab->move_right = 0;
	else if (keycode == 257 || keycode == 258)
		tab->movspeed = 0.02 + 0.04 * tab->switchtex;
	return (0);
}

void	move_side(t_cub3d *tab)
{
	if (tab->move_right == 1)
	{
		if (tab->carte[(int)(tab->posx + tab->planx * tab->movspeed)]
		[(int)tab->posy] == 0 || tab->carte[(int)(tab->posx + tab->planx
		* tab->movspeed)][(int)tab->posy] == 3)
			tab->posx += tab->planx * tab->movspeed;
		if (tab->carte[(int)(tab->posx)][(int)(tab->posy + tab->plany *
		tab->movspeed)] == 0 || tab->carte[(int)(tab->posx)]
		[(int)(tab->posy + tab->plany * tab->movspeed)] == 3)
			tab->posy += tab->plany * tab->movspeed;
	}
	if (tab->move_left == 1)
	{
		if (tab->carte[(int)(tab->posx + tab->planx * tab->movspeed)]
		[(int)tab->posy] == 0 || tab->carte[(int)(tab->posx + tab->planx
		* tab->movspeed)][(int)tab->posy] == 3)
			tab->posx -= tab->planx * tab->movspeed;
		if (tab->carte[(int)(tab->posx)][(int)(tab->posy - tab->plany
		* tab->movspeed)] == 0 || tab->carte[(int)(tab->posx)][(int)(tab->posy
		- tab->plany * tab->movspeed)] == 3)
			tab->posy -= tab->plany * tab->movspeed;
	}
	turn(tab);
}

void	turn_bis(t_cub3d *tab)
{
	if (tab->turn_left == 1)
	{
		tab->olddirx = tab->dirx;
		tab->dirx = tab->dirx * cos(tab->rotspeed)
			- tab->diry * sin(tab->rotspeed);
		tab->diry = tab->olddirx * sin(tab->rotspeed)
			+ tab->diry * cos(tab->rotspeed);
		tab->oldplanx = tab->planx;
		tab->planx = tab->planx * cos(tab->rotspeed)
			- tab->plany * sin(tab->rotspeed);
		tab->plany = tab->oldplanx * sin(tab->rotspeed)
			+ tab->plany * cos(tab->rotspeed);
	}
}

int		move(t_cub3d *tab)
{
	if (tab->move_up == 1)
	{
		if (tab->carte[(int)(tab->posx + tab->dirx * tab->movspeed)]
		[(int)tab->posy] == 0 || tab->carte[(int)(tab->posx + tab->dirx
		* tab->movspeed)][(int)tab->posy] == 3)
			tab->posx += tab->dirx * tab->movspeed;
		if (tab->carte[(int)(tab->posx)][(int)(tab->posy + tab->diry *
		tab->movspeed)] == 0 || tab->carte[(int)(tab->posx)][(int)(tab->posy
		+ tab->diry * tab->movspeed)] == 3)
			tab->posy += tab->diry * tab->movspeed;
	}
	if (tab->move_down == 1)
	{
		if (tab->carte[(int)(tab->posx - tab->dirx * tab->movspeed)]
		[(int)tab->posy] == 0 || tab->carte[(int)(tab->posx - tab->dirx
		* tab->movspeed)][(int)tab->posy] == 3)
			tab->posx -= tab->dirx * tab->movspeed;
		if (tab->carte[(int)(tab->posx)][(int)(tab->posy - tab->diry *
		tab->movspeed)] == 0 || tab->carte[(int)(tab->posx)][(int)(tab->posy
		- tab->diry * tab->movspeed)] == 3)
			tab->posy -= tab->diry * tab->movspeed;
	}
	move_side(tab);
	ft_ray(tab);
	return (0);
}
