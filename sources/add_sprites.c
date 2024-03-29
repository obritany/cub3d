/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:10:41 by obritany          #+#    #+#             */
/*   Updated: 2021/03/06 16:10:43 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_ray(t_game *gm)
{
	gm->raycast[gm->ray.i].x = gm->ray.x;
	gm->raycast[gm->ray.i].y = gm->ray.y;
	gm->raycast[gm->ray.i].d = gm->hit.d;
}

void	draw_sprite(t_game *gm, int place, double spr_d)
{
	double			size;
	unsigned int	clr;
	unsigned int	id;
	int				i;
	int				j;

	size = gm->win.y / spr_d;
	place = place - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((place + i >= 0 && place + i < gm->win.x) &&
			(j < size && gm->raycast[place + i].d > spr_d))
		{
			clr = XPM * floor(XPM * (double)j / size) + XPM * (double)i / size;
			clr = gm->txr.sprt[clr];
			id = place + i + (gm->win.y / 2 - floor(size / 2) + j) * gm->win.x;
			if (id < (unsigned int)(gm->win.x * gm->win.y))
				gm->img.adr[id] = (clr == NO_COLOR) ? gm->img.adr[id] : clr;
			j++;
		}
		i++;
	}
}

int		get_sprt_plc(t_game *gm, double spr_x, double spr_y, double spr_d)
{
	double	ang;
	double	dir_x;
	double	dir_y;

	dir_x = (spr_x - gm->pos.x) / spr_d;
	dir_y = (spr_y - gm->pos.y) / spr_d;
	if (dir_y <= 0)
		ang = acos(dir_x) * 180 / M_PI;
	else
		ang = 360 - acos(dir_x) * 180 / M_PI;
	ang = gm->dir.a - ang + FOV / 2;
	if (ang >= 180)
		ang -= 360;
	if (ang <= -180)
		ang += 360;
	return ((ang / FOV) * gm->win.x);
}

void	sort_sprites(t_game *gm)
{
	t_sprt	temp;
	int		i;

	i = 0;
	while (i < gm->map.sprt_num - 1)
	{
		if (gm->sprt[i].d < gm->sprt[i + 1].d)
		{
			temp = gm->sprt[i];
			gm->sprt[i] = gm->sprt[i + 1];
			gm->sprt[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	add_sprites(t_game *gm)
{
	int	i;
	int	place;

	if (gm->dir.y <= 0)
		gm->dir.a = acos(gm->dir.x) * 180 / M_PI;
	else
		gm->dir.a = 360 - acos(gm->dir.x) * 180 / M_PI;
	i = 0;
	while (i < gm->map.sprt_num)
	{
		gm->sprt[i].d =
				hypot(gm->sprt[i].x - gm->pos.x, gm->sprt[i].y - gm->pos.y);
		i++;
	}
	sort_sprites(gm);
	i = 0;
	while (i < gm->map.sprt_num)
	{
		place = get_sprt_plc(gm, gm->sprt[i].x, gm->sprt[i].y, gm->sprt[i].d);
		draw_sprite(gm, place, gm->sprt[i].d);
		i++;
	}
	free(gm->raycast);
}
