#include "cub3d.h"

int				ft_true_height(t_all *s)
{
	double	factor;
	double	ang;
	int		height;

	ang = fabs((double)s->ray.i / ((double)s->win.x / 2) - 1);
	ang = ang * ((FOV / 2) * M_PI / 180);
	factor = s->hit.d * cos(ang);
	height = round(s->win.y / factor);
	return (height);
}

unsigned int	ft_get_color(t_all *s, double i)
{
	int pxid;

	if (floor(s->hit.y) == s->hit.y)
	{
		pxid = XPM_SIZE * floor(XPM_SIZE * i) + XPM_SIZE * (s->hit.x - floor(s->hit.x));
		if (s->ray.w == 1)
			return (s->tex.s[pxid]);
		if (s->ray.w == 0)
			return (s->tex.n[pxid]);
	}
	if (floor(s->hit.x) == s->hit.x)
	{
		pxid = XPM_SIZE * floor(XPM_SIZE * i) + XPM_SIZE * (s->hit.y - floor(s->hit.y));
		if (s->ray.v == 1)
			return (s->tex.e[pxid]);
		if (s->ray.v == 0)
			return (s->tex.w[pxid]);
	}
	return (NO_COLOR);
}

void			ft_draw_column(t_all *s)
{
	int				height;
	int				start;
	int				steps;
	int				x;
	unsigned int	color;

	height = ft_true_height(s);
	start = s->win.x * (s->win.y - height) / 2;
	steps = (height > s->win.y) ? (height - s->win.y) / 2 : 0;
	x = s->ray.i;
	while (x < s->win.x * s->win.y)
	{
		color = s->tex.c;
		if (x >= start && steps < height)
		{
			color = ft_get_color(s, (double) steps / height);
			steps++;
		}
		if (steps == height)
			color = s->tex.f;
		s->img.adr[x] = color;
		x += s->win.x;
	}
}
