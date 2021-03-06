/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:11:21 by obritany          #+#    #+#             */
/*   Updated: 2021/03/06 16:11:23 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_frame(t_game *gm, int mode)
{
	gm->ray.x = 0;
	gm->ray.y = 0;
	gm->ray.i = 0;
	gm->ray.e = 0;
	gm->ray.s = 0;
	gm->hit.x = 0;
	gm->hit.y = 0;
	gm->hit.d = 0;
	if (draw_image(gm) == -1)
		close_app(gm, !mode);
	add_sprites(gm);
	if (mode == 1)
		return ;
	mlx_put_image_to_window(gm->mlx.ptr, gm->win.ptr, gm->img.ptr, 0, 0);
	free(gm->img.ptr);
	free(gm->img.adr);
}

int		setup_mlx(t_game gm, char *map, int mode)
{
	gm.dir.x = 0;
	gm.dir.y = 0;
	gm.pos.x = 0;
	gm.pos.y = 0;
	gm.mlx.ptr = mlx_init();
	if (read_map_file(&gm, map) == -1)
		close_app(&gm, 0);
	if (mode == 1)
		save_bmp(&gm);
	gm.win.ptr = mlx_new_window(gm.mlx.ptr, gm.win.x, gm.win.y, "cub3d");
	refresh_frame(&gm, 0);
	refresh_frame(&gm, 0);
	mlx_hook(gm.win.ptr, 2, 0, control, &gm);
	mlx_hook(gm.win.ptr, 17, 0, close_app, &gm);
	mlx_loop(gm.mlx.ptr);
	return (1);
}

void	setup_game(t_game gm, char *cub, int bmp)
{
	gm.map.arr = 0;
	gm.map.x = 0;
	gm.map.y = 0;
	gm.map.sprt_num = 0;
	gm.txr.north = 0;
	gm.txr.south = 0;
	gm.txr.east = 0;
	gm.txr.west = 0;
	gm.txr.sprt = 0;
	gm.sprt = 0;
	gm.raycast = 0;
	gm.txr.up = NO_COLOR;
	gm.txr.down = NO_COLOR;
	setup_mlx(gm, cub, bmp);
}

void	load_game(char *map, int mode)
{
	t_game	gm;

	gm.win.x = 0;
	gm.win.y = 0;
	gm.win.ptr = 0;
	gm.mlx.ptr = 0;
	gm.img.ptr = 0;
	gm.img.adr = 0;
	gm.error.num = 0;
	gm.error.map_mode = 0;
	gm.error.pos_num = 0;
	setup_game(gm, map, mode);
}

int		main(int argc, char *argv[])
{
	if (argc == 3 &&
			!ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) &&
			!ft_strncmp(argv[2], "--save", 6))
		load_game(argv[1], 1);
	else if (argc == 2 &&
			!ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4))
		load_game(argv[1], 0);
	else
		print_error(-10);
	return (0);
}
