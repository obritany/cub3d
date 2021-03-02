#include "cub3d.h"

void	ft_draw(t_all *s, int mode)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	s->ray = ray;
	s->hit = hit;
	ft_draw_image(s);
	ft_add_sprites(s);
	if (mode == 1)
		return ;
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);
	free(s->img.ptr);
	free(s->img.adr);
}

int		ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;
	t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	s.pos = pos;
	s.dir = dir;
	s.mlx.ptr = mlx_init();
	if (ft_parse(&s, cub) == -1)
		ft_close(&s, 0);
	if (bmp == 1)
		ft_bitmap(&s);
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");
	ft_draw(&s, 0);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);
	return (1);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_map	map;
	t_tex	tex;
	t_spr	*spr;
	t_stk	*stk;

	map.tab = 0;
	tex.n = 0;
	tex.s = 0;
	tex.e = 0;
	tex.w = 0;
	tex.i = 0;
	spr = 0;
	stk = 0;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	tex.c = NO_COLOR;
	tex.f = NO_COLOR;
	s.map = map;
	s.tex = tex;
	s.spr = spr;
	s.stk = stk;
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;

	mlx.ptr = 0;
	win.ptr = 0;
	img.ptr = 0;
	img.adr = 0;
	win.x = 0;
	win.y = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.err = err;
	ft_declare(s, cub, bmp);
}

int		main(int argc, char *argv[])
{
	if (argc == 3 && !ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) &&
			!ft_strncmp(argv[2], "--save", 6))
		ft_init(argv[1], 1);
	else if (argc == 2 && !ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4))
		ft_init(argv[1], 0);
	else
		ft_putstr_fd("Error : Invalid arguments\n", 2);
	return (0);
}
