/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:36:52 by obritany          #+#    #+#             */
/*   Updated: 2021/03/06 16:36:53 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hit_horizontal(t_game *gm)
{
	double	x;
	double	y;

	y = floor(gm->pos.y) + gm->ray.s;
	x = gm->pos.x + (y - gm->pos.y) * (gm->ray.x / gm->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < gm->map.x)
	{
		if (gm->map.arr[(int)(y - 1 + gm->ray.s)][(int)floor(x)] == ' ')
			break ;
		if (gm->map.arr[(int)(y - 1 + gm->ray.s)][(int)floor(x)] == '1')
		{
			if (gm->hit.d > hypot(x - gm->pos.x, y - gm->pos.y))
			{
				gm->hit.x = x;
				gm->hit.y = y;
				gm->hit.d = hypot(x - gm->pos.x, y - gm->pos.y);
			}
			return ;
		}
		y += (2 * gm->ray.s - 1);
		x += (2 * gm->ray.s - 1) * gm->ray.x / gm->ray.y;
	}
}

void	hit_vertical(t_game *gm)
{
	double	x;
	double	y;

	x = floor(gm->pos.x) + gm->ray.e;
	y = gm->pos.y + (x - gm->pos.x) * (gm->ray.y / gm->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < gm->map.y)
	{
		if (gm->map.arr[(int)floor(y)][(int)(x - 1 + gm->ray.e)] == ' ')
			break ;
		if (gm->map.arr[(int)floor(y)][(int)(x - 1 + gm->ray.e)] == '1')
		{
			gm->hit.x = x;
			gm->hit.y = y;
			gm->hit.d = hypot(x - gm->pos.x, y - gm->pos.y);
			return ;
		}
		x += (2 * gm->ray.e - 1);
		y += (2 * gm->ray.e - 1) * gm->ray.y / gm->ray.x;
	}
	gm->hit.d = 999999;
}

void	get_ray_dir(t_game *gm)
{
	double	ang;

	ang = (double)gm->ray.i / (gm->win.x / 2) - 1;
	ang = ang * ((FOV / 2) * M_PI / 180);
	gm->ray.x = gm->dir.x * cos(ang) - gm->dir.y * sin(ang);
	gm->ray.y = gm->dir.y * cos(ang) + gm->dir.x * sin(ang);
	gm->ray.e = (gm->ray.x >= 0) ? 1 : 0;
	gm->ray.s = (gm->ray.y >= 0) ? 1 : 0;
}

int		draw_image(t_game *gm)
{
	int	bits;
	int	size;
	int	endian;

	gm->img.ptr = mlx_new_image(gm->mlx.ptr, gm->win.x, gm->win.y);
	gm->img.adr = (unsigned int *)
			mlx_get_data_addr(gm->img.ptr, &bits, &size, &endian);
	if ((gm->raycast = malloc(sizeof(t_raycast) * gm->win.x)) == 0)
		return (print_error(-6));
	while (gm->ray.i < gm->win.x)
	{
		get_ray_dir(gm);
		hit_vertical(gm);
		hit_horizontal(gm);
		save_ray(gm);
		draw_column(gm);
		gm->ray.i++;
	}
	return (1);
}
