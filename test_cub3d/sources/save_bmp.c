#include "cub3d.h"

void	add_header(t_game *gm, int fd)
{
	int		n;
	char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = 0;
	header[0] = 66;
	header[1] = 77;
	n = gm->win.x * gm->win.y * 4 + 54;
	header[2] = n;
	header[3] = n >> 8;
	header[4] = n >> 16;
	header[5] = n >> 24;
	header[10] = 54;
	write(fd, header, 14);
}

void	add_info(t_game *gm, int fd)
{
	int		n;
	char	info[40];

	n = 0;
	while (n < 40)
		info[n++] = 0;
	info[0] = 40;
	n = gm->win.x;
	info[4] = n;
	info[5] = n >> 8;
	info[6] = n >> 16;
	info[7] = n >> 24;
	n = gm->win.y;
	info[8] = n;
	info[9] = n >> 8;
	info[10] = n >> 16;
	info[11] = n >> 24;
	info[12] = 1;
	info[14] = 32;
	write(fd, info, 40);
}

void	add_data(t_game *gm, int fd)
{
	int		i;
	int		j;
	char	data[4];

	i = gm->win.x * (gm->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < gm->win.x)
		{
			data[0] = gm->img.adr[i];
			data[1] = gm->img.adr[i] >> 8;
			data[2] = gm->img.adr[i] >> 16;
			data[3] = 0;
			write(fd, data, 4);
			i++;
			j++;
		}
		i -= 2 * gm->win.x;
	}
}

void	save_bmp(t_game *gm)
{
	int		fd;

	refresh_frame(gm, 1);
	free(gm->img.ptr);
	free(gm->img.adr);
	refresh_frame(gm, 1);
	fd = creat("screen.bmp", S_IRWXU);
	add_header(gm, fd);
	add_info(gm, fd);
	add_data(gm, fd);
	close(fd);
	free(gm->img.ptr);
	free(gm->img.adr);
	close_app(gm, 0);
}
