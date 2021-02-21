#include "cub3d.h"

void	ft_ray(t_all *s)
{
	double	angle;

	angle = (double)s->ray.i / (s->win.x / 2) - 1;	//angle from -1 to 1
	angle = angle * (30 * M_PI / 180);				//angle in radians
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);

	angle = angle * (180/M_PI);
	if (angle == 0)
	{
		printf("\n");
//		printf("angle - %.1f\n", angle);
		printf("dir_x - %.1f\n", s->dir.x);
		printf("dir_y - %.1f\n", s->dir.y);
		printf("ray_x - %.1f\n", s->ray.x);
		printf("ray_y - %.1f\n", s->ray.y);
		printf("ray_y/x - %.1f\n", (s->ray.y / s->ray.x));
		printf("pos_x - %.1f\n", s->pos.x);
		printf("pos_y - %.1f\n", s->pos.y);
	}

	//dir_W: x = -1, y = 0
	//dir_E: x = 1,  y = 0
	//dir_N: x = 0,  y = -1
	//dir_E: x = 0,  y = 1

}

void	ft_dir(t_all *s)
{
	if (s->ray.x >= 0)
		s->ray.v = 1;		// east side
	else
		s->ray.v = 0;		// west side
	if (s->ray.y >= 0)
		s->ray.w = 1;		// south side
	else
		s->ray.w = 0;		// norh side
}

void	ft_ver(t_all *s)
{
	double	x;
	double	y;

	x = floor(s->pos.x) + s->ray.v;
	y = s->pos.y + (x - s->pos.x) * (s->ray.y / s->ray.x);

//	printf("x - %.1f\n", x);
//	printf("y - %.1f\n", y);

	while ((int)floor(y) > 0 && (int)floor(y) < s->map.y)
	{
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

void	ft_hor(t_all *s)
{
	double	y;
	double	x;

	y = floor(s->pos.y) + s->ray.w;
	x = s->pos.x + (y - s->pos.y) * (s->ray.x / s->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < s->map.x)
	{
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

void	ft_screen(t_all *s)
{
	int		bpp;
	int		sl;
	int		end;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	while (s->ray.i < s->win.x)
	{
		ft_ray(s);
		ft_dir(s);
		ft_ver(s);
		ft_hor(s);
		ft_column(s, ft_size(s));
		s->ray.i++;
	}
//	ft_sprite(s);
}
