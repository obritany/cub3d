#include "cub3d.h"

int				get_true_height(t_game *gm)
{
	double	factor;
	double	ang;
	int		height;

	ang = fabs((double)gm->ray.i / ((double)gm->win.x / 2) - 1);
	ang = ang * ((FOV / 2) * M_PI / 180);
	factor = gm->hit.d * cos(ang);
	height = round(gm->win.y / factor);
	return (height);
}

unsigned int	get_color(t_game *gm, double i)
{
	unsigned int pxid;

	if (floor(gm->hit.y) == gm->hit.y)
	{
		pxid = XPM_SIZE * floor(XPM_SIZE * i) + XPM_SIZE * (gm->hit.x - floor(gm->hit.x));
		if (gm->ray.s == 1)
			return (gm->txr.south[pxid]);
		if (gm->ray.s == 0)
			return (gm->txr.north[pxid]);
	}
	if (floor(gm->hit.x) == gm->hit.x)
	{
		pxid = XPM_SIZE * floor(XPM_SIZE * i) + XPM_SIZE * (gm->hit.y - floor(gm->hit.y));
		if (gm->ray.e == 1)
			return (gm->txr.east[pxid]);
		if (gm->ray.e == 0)
			return (gm->txr.west[pxid]);
	}
	return (NO_COLOR);
}

void			draw_column(t_game *gm)
{
	int				height;
	int				start;
	int				steps;
	int				x;
	unsigned int	color;

	height = get_true_height(gm);
	start = gm->win.x * (gm->win.y - height) / 2;
	steps = (height > gm->win.y) ? (height - gm->win.y) / 2 : 0;
	x = gm->ray.i;
	while (x < gm->win.x * gm->win.y)
	{
		color = gm->txr.up;
		if (x >= start && steps < height)
		{
			color = get_color(gm, (double) steps / height);
			steps++;
		}
		if (steps == height)
			color = gm->txr.down;
		gm->img.adr[x] = color;
		x += gm->win.x;
	}
}
