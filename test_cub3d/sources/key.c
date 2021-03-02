#include "cub3d.h"

int		ft_close(t_all *s, int win)
{
	int	i;

	i = 0;
	while (i < s->map.y)
		free(s->map.tab[i++]);
	free(s->map.tab);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	free(s->tex.i);
	if (win == 1)
		mlx_destroy_window(s->mlx.ptr, s->win.ptr);
	free(s->mlx.ptr);
	exit(0);
	return (1);
}

void	ft_move(t_all *s, double c)
{
	char cell;

	s->pos.x += c * (s->dir.x * SPEED / 100);
	cell = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (cell == '1' || cell == '2')
		s->pos.x -= c * (s->dir.x * SPEED / 100);
	s->pos.y += c * (s->dir.y * SPEED / 100);
	cell = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (cell == '1' || cell == '2')
		s->pos.y -= c * (s->dir.y * SPEED / 100);
}

void	ft_strafe(t_all *s, double c)
{
	char cell;

	s->pos.x -= c * (s->dir.y * SPEED / 100);
	cell = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (cell == '1' || cell == '2')
		s->pos.x += c * (s->dir.y * SPEED / 100);
	s->pos.y += c * (s->dir.x * SPEED / 100);
	cell = s->map.tab[(int)floor(s->pos.y)][(int)floor(s->pos.x)];
	if (cell == '1' || cell == '2')
		s->pos.y -= c * (s->dir.x * SPEED / 100);
}

void	ft_rotate(t_all *s, double c)
{
	double	dist;

	s->dir.x = s->dir.x * cos(c * TURN) - s->dir.y * sin(c * TURN);
	s->dir.y = s->dir.y * cos(c * TURN) + s->dir.x * sin(c * TURN);
	dist = hypot(s->dir.x, s->dir.y);
	s->dir.x /= dist;
	s->dir.y /= dist;
}

int	ft_key(int key, t_all *s)
{
	if (key == ESC)
		ft_close(s, 1);
	else if (key == W)
		ft_move(s, 1);
	else if (key == S)
		ft_move(s, -1);
	else if (key == D)
		ft_strafe(s, 1);
	else if (key == A)
		ft_strafe(s, -1);
	else if (key == RIGHT)
		ft_rotate(s, 1);
	else if (key == LEFT)
		ft_rotate(s, -1);
	ft_draw(s, 0);
	return (1);
}
