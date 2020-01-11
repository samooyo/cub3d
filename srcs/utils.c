/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 21:26:44 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/11 19:15:49 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_game(t_cub3d *tab)
{
	free_game(tab);
	exit(0);
	return (0);
}

int		ft_square(int a)
{
	return (a * a);
}

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

void	ft_print_map(t_cub3d *tab, int nbrline, int lenline)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (j < nbrline)
	{
		i = 0;
		while (i < (lenline / 2 + 1))
		{
			printf("%d", tab->carte[i][j]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	turn(t_cub3d *tab)
{
	if (tab->turn_right == 1)
	{
		tab->olddirx = tab->dirx;
		tab->dirx = tab->dirx * cos(-tab->rotspeed) -
			tab->diry * sin(-tab->rotspeed);
		tab->diry = tab->olddirx * sin(-tab->rotspeed)
			+ tab->diry * cos(-tab->rotspeed);
		tab->oldplanx = tab->planx;
		tab->planx = tab->planx * cos(-tab->rotspeed)
			- tab->plany * sin(-tab->rotspeed);
		tab->plany = tab->oldplanx * sin(-tab->rotspeed)
			+ tab->plany * cos(-tab->rotspeed);
	}
	turn_bis(tab);
}
