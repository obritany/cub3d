#include "cub3d.h"

unsigned int	ft_pixel(t_all *s, double i)
{
	int				index;

	if (floor(s->hit.y) == s->hit.y)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x));
		if (s->ray.w == 1)
			return (s->tex.s[index]);
		if (s->ray.w == 0)
			return (s->tex.n[index]);
	}
	else if (floor(s->hit.x) == s->hit.x)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
		if (s->ray.v == 1)
			return (s->tex.e[index]);
		if (s->ray.v == 0)
			return (s->tex.w[index]);
	}
	return (BLACK);
}

void			ft_column(t_all *s, int size)
{
	unsigned int	color;
	int				start;
	int				count;
	int				x;

	start = s->win.x * (s->win.y - size) / 2;
	if (size > s->win.y)
		count = (size - s->win.y) / 2;
	else
		count = 0;
	x = s->ray.i;
	while (x < s->win.x * s->win.y)
	{
		color = s->tex.c;
		if (x >= start && count < size)
		{
			color = ft_pixel(s, (double)count / size);
			count++;
		}
		if (count == size)
			color = s->tex.f;

		s->img.adr[x] = mlx_get_color_value(s->mlx.ptr, color);
		x += s->win.x;
	}
}

int				ft_size(t_all *s)
{
	double	correc;
	double	angle;
	int		size;

	angle = fabs((double)s->ray.i / (s->win.x / 2) - 1);
	angle = angle * (30 * M_PI / 180);
	correc = s->hit.d * cos(angle);
	size = round(s->win.y / correc);
	return (size);
}
