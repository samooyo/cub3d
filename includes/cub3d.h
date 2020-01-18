/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:21:33 by sadarnau          #+#    #+#             */
/*   Updated: 2020/01/18 15:41:09 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include "get_next_line.h"

# define MSG0 "Error\nScreen Resolution error"
# define MSG1 "Error\nColor error"
# define MSG2 "Error\nTexture error"
# define MSG3 "Error\nMap error"
# define MSG4 "Error\nInitialization error"
# define MSG5 "Error\nSprite error"
# define MSG6 "Error\nArgument error"

typedef struct		s_bmp
{
	int				padding;
	unsigned char	signature[2];
	unsigned int	totalsize;
	unsigned int	offset;
	unsigned int	bm_headersize;
	unsigned int	imagesize;
	unsigned int	width;
	unsigned int	height;
	unsigned short	planes_number;
	unsigned short	bpp;
	unsigned int	compression_type;
	unsigned int	hres;
	unsigned int	vres;
	unsigned int	ncolors;
	unsigned int	nimpcolors;
}					t_bmp;

typedef struct		s_tex
{
	char			*datatex;
	int				height;
	int				width;
	int				sizeline;
	int				bpp;
	int				endian;
	void			*tex;
	double			x;
	double			y;
}					t_tex;

typedef struct		s_spr
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				sprscreenx;
	int				h;
	int				drawstarty;
	int				drawendy;
	int				w;
	int				drawstartx;
	int				drawendx;
	int				y;
	int				stripe;
	int				texx;
	int				d;
	int				texy;
	int				color;
}					t_spr;

typedef struct		s_cub3d
{
	char			*img_ptr;
	char			*name;
	int				i;
	int				j;
	int				lenline;
	int				nbrline;
	int				winx;
	int				winy;
	int				drawstart;
	int				drawend;
	int				hauteurligne;
	int				**carte;
	int				*sprposi;
	int				clr[4];
	int				nbrspr;
	int				texy;
	int				texx;
	int				d;
	int				bpp;
	int				switchtex;
	int				x;
	int				y;
	int				bitspp;
	int				sizeline;
	int				endian;
	int				move_down;
	int				move_right;
	int				move_left;
	int				move_up;
	int				turn_right;
	int				turn_left;
	int				mapx;
	int				mapy;
	int				floortexx;
	int				floortexy;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				floor_color;
	int				ceil_color;
	int				save;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			dist2wall;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	double			movspeed;
	double			rotspeed;
	double			olddirx;
	double			oldplanx;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;
	double			perswdis;
	double			floorx;
	double			floory;
	double			currentdist;
	double			floorxx;
	double			flooryy;
	double			wallx;
	double			*zbuf;
	void			*mlx;
	void			*win;
	void			*img;
	t_tex			*no;
	t_tex			*so;
	t_tex			*we;
	t_tex			*ea;
	t_tex			*floor;
	t_tex			*ceilling;
	t_tex			*sprite;
	t_spr			*spr;
}					t_cub3d;

int					ft_strlen(char *str);
int					ft_isdigit(int c);
int					key_press(int keycode, t_cub3d *tab);
int					key_release(int keycode, t_cub3d *tab);
int					move(t_cub3d *tab);
void				ft_initialize_tab(t_cub3d *tab);
void				load_tex(t_cub3d *tab);
void				ft_wall_tex(t_cub3d *tab);
void				ft_parser(t_cub3d *tab, char *name);
void				ft_ray(t_cub3d *tab);
void				ft_draw(t_cub3d *tab);
void				turn(t_cub3d *tab);
void				turn_bis(t_cub3d *tab);
void				ft_res(t_cub3d *tab, char *str);
int					mlx_get_pixel_clr(t_tex *tex, int x, int y);
int					mlx_put_pixel(t_cub3d *tab, int x, int y, int clr);
void				floor_direction(t_cub3d *tab);
void				draw_floor(t_cub3d *tab);
void				ft_sprite(t_cub3d *tab, int i);
int					ft_colorgrad(t_cub3d *tab, int c);
void				ft_screen_res(t_cub3d *tab, char *name);
void				ft_error(t_cub3d *tab, int er);
void				ft_color_check(t_cub3d *tab, char *str, int floor);
int					generate_clr(int r, int g, int b);
int					ft_isdigit(int c);
void				ft_parse_tex(t_cub3d *tab, char *str);
int					ft_last_line(char **ptr, char **line, int fd);
void				ft_load_sprite(t_cub3d *tab, char *str);
void				ft_sprite(t_cub3d *tab, int i);
void				ft_sort_spr(t_cub3d *tab);
int					ft_square(int a);
void				ft_parse_map(t_cub3d *tab, char *str, int fd);
int					ft_nbr_map(t_cub3d *tab, char *str, int fd, int *lenline);
void				save_bmp(t_cub3d *tab);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_write(void);
void				free_game(t_cub3d *tab);
int					exit_game(t_cub3d *tab);

#endif
