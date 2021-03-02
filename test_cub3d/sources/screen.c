#include "cub3d.h"

void	ft_horizontal(t_all *s)
{
	double	x;
	double	y;

	y = floor(s->pos.y) + s->ray.w;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
	{
		if (s->map.tab[(int)(y - 1 + s->ray.w)][(int)floor(x)] == ' ')
			break ;
		if (s->map.tab[(int)(y - 1 + s->ray.w)][(int)floor(x)] == '1')
		{
			if (s->hit.d > hypot(x - s->pos.x, y - s->pos.y))
			{
				s->hit.x = x;
				s->hit.y = y;
				s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			}
			return ;
		}
		y += (2 * s->ray.w - 1);
		x += (2 * s->ray.w - 1) * s->ray.x / s->ray.y;
	}
}

void	ft_vertical(t_all *s)
{
	double	x;
	double	y;

	x = floor(s->pos.x) + s->ray.v;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
		if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.v)] == ' ')
			break ;
		if (s->map.tab[(int)floor(y)][(int)(x - 1 + s->ray.v)] == '1')
		{
			s->hit.x = x;
			s->hit.y = y;
			s->hit.d = hypot(x - s->pos.x, y - s->pos.y);
			return ;
		}
		x += (2 * s->ray.v - 1);
		y += (2 * s->ray.v - 1) * s->ray.y / s->ray.x;
	}
	s->hit.d = 999999;
}

void	ft_ray_dir(t_all *s)
{
	double	ang;

	ang = (double)s->ray.i / (s->win.x / 2) - 1;		//ang from -1 to 1
	ang = ang * ((FOV / 2) * M_PI / 180);				//ang in radians
	s->ray.x = s->dir.x * cos(ang) - s->dir.y * sin(ang);
	s->ray.y = s->dir.y * cos(ang) + s->dir.x * sin(ang);
	s->ray.v = (s->ray.x >= 0) ? 1 : 0;
	s->ray.w = (s->ray.y >= 0) ? 1 : 0;
}

void	ft_draw_image(t_all *s)
{
	int	bits;
	int	size;
	int	endian;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bits, &size, &endian);
	s->stk = malloc(sizeof(t_stk) * s->win.x);
	while (s->ray.i < s->win.x)
	{
		ft_ray_dir(s);
		ft_vertical(s);
		ft_horizontal(s);
		ft_save_ray(s);
		ft_draw_column(s);
		s->ray.i++;
	}
}
