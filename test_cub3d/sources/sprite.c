#include "cub3d.h"

void	ft_save_ray(t_all *s)
{
	s->stk[s->ray.i].x = s->ray.x;
	s->stk[s->ray.i].y = s->ray.y;
	s->stk[s->ray.i].d = s->hit.d;
}

void	ft_draw_sprite(t_all *s, int place, double spr_d)
{
	double			size;
	unsigned int	color;
	unsigned int	pxid;
	int				i;
	int				j;

	size = (s->win.y / spr_d);
	place = place - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while ((place + i >= 0 && place + i < s->win.x) &&
			   (j < size && s->stk[place + i].d > spr_d))
		{
			color = XPM_SIZE * floor(XPM_SIZE * (double)j / size) + XPM_SIZE * (double)i / size;
			color = s->tex.i[color];
			pxid = place + i + (s->win.y / 2 - floor(size / 2) + j) * s->win.x;
			if (pxid < s->win.x * s->win.y)
				s->img.adr[pxid] = (color == NO_COLOR) ? s->img.adr[pxid] : color;
			j++;
		}
		i++;
	}
}

int		ft_sprite_place(t_all *s, double spr_x, double spr_y, double spr_d)
{
	double	ang;
	double	dir_x;
	double	dir_y;

	dir_x = (spr_x - s->pos.x) / spr_d;
	dir_y = (spr_y - s->pos.y) / spr_d;
	if (dir_y <= 0)
		ang = acos(dir_x) * 180 / M_PI;
	else
		ang = 360 - acos(dir_x) * 180 / M_PI;
	ang = s->dir.a - ang + FOV / 2;
	if (ang >= 180)
		ang -= 360;
	if (ang <= -180)
		ang += 360;
	return ((ang / FOV) * s->win.x);
}

void	ft_sort_sprites(t_all *s)
{
	t_spr	temp;
	int		i;

	i = 0;
	while (i < s->map.spr - 1)
	{
		if (s->spr[i].d < s->spr[i + 1].d)
		{
			temp = s->spr[i];
			s->spr[i] = s->spr[i + 1];
			s->spr[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

void	ft_add_sprites(t_all *s)
{
	int	i;
	int	place;

	if (s->dir.y <= 0)
		s->dir.a = acos(s->dir.x) * 180 / M_PI;
	else
		s->dir.a = 360 - acos(s->dir.x) * 180 / M_PI;
	i = 0;
	while (i < s->map.spr)
	{
		s->spr[i].d = hypot(s->spr[i].x - s->pos.x, s->spr[i].y - s->pos.y);
		i++;
	}
	ft_sort_sprites(s);
	i = 0;
	while (i < s->map.spr)
	{
		place = ft_sprite_place(s, s->spr[i].x, s->spr[i].y, s->spr[i].d);
		ft_draw_sprite(s, place, s->spr[i].d);
		i++;
	}
	free(s->stk);
}
