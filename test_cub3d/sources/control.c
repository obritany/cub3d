#include "cub3d.h"

void	make_turn(t_game *gm, double c)
{
	double	distance;

	gm->dir.x = gm->dir.x * cos(c * TRN_ANG) - gm->dir.y * sin(c * TRN_ANG);
	gm->dir.y = gm->dir.y * cos(c * TRN_ANG) + gm->dir.x * sin(c * TRN_ANG);
	distance = hypot(gm->dir.x, gm->dir.y);
	gm->dir.x /= distance;
	gm->dir.y /= distance;
}

void	move_fb(t_game *gm, double dir)
{
	char new_pos;

	gm->pos.x += dir * (gm->dir.x * MV_SPD / 100);
	new_pos = gm->map.array[(int)floor(gm->pos.y)][(int)floor(gm->pos.x)];
	if (new_pos == '1' || new_pos == '2')
		gm->pos.x -= dir * (gm->dir.x * MV_SPD / 100);
	gm->pos.y += dir * (gm->dir.y * MV_SPD / 100);
	new_pos = gm->map.array[(int)floor(gm->pos.y)][(int)floor(gm->pos.x)];
	if (new_pos == '1' || new_pos == '2')
		gm->pos.y -= dir * (gm->dir.y * MV_SPD / 100);
}

void	move_lr(t_game *gm, double dir)
{
	char new_pos;

	gm->pos.x -= dir * (gm->dir.y * MV_SPD / 100);
	new_pos = gm->map.array[(int)floor(gm->pos.y)][(int)floor(gm->pos.x)];
	if (new_pos == '1' || new_pos == '2')
		gm->pos.x += dir * (gm->dir.y * MV_SPD / 100);
	gm->pos.y += dir * (gm->dir.x * MV_SPD / 100);
	new_pos = gm->map.array[(int)floor(gm->pos.y)][(int)floor(gm->pos.x)];
	if (new_pos == '1' || new_pos == '2')
		gm->pos.y -= dir * (gm->dir.x * MV_SPD / 100);
}

int		close_app(t_game *gm, int window)
{
	int	i;

	i = 0;
	while (i < gm->map.y)
		free(gm->map.array[i++]);
	free(gm->map.array);
	free(gm->txr.north);
	free(gm->txr.south);
	free(gm->txr.east);
	free(gm->txr.west);
	free(gm->txr.sprt);
	if (window == 1)
		mlx_destroy_window(gm->mlx.ptr, gm->win.ptr);
	free(gm->mlx.ptr);
	exit(0);
	return (1);
}

int	control(int key, t_game *gm)
{
	if (key == W)
		move_fb(gm, 1);
	if (key == S)
		move_fb(gm, -1);
	if (key == D)
		move_lr(gm, 1);
	if (key == A)
		move_lr(gm, -1);
	if (key == RIGHT)
		make_turn(gm, 1);
	if (key == LEFT)
		make_turn(gm, -1);
	if (key == ESC)
		close_app(gm, 1);
	refresh_frame(gm, 0);
	return (1);
}
