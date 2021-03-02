#include "cub3d.h"

void	ft_bdata(t_all *s, int fd)
{
	int		i;
	int		j;
	char	buffer[4];

	i = s->win.x * (s->win.y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < s->win.x)
		{
			buffer[0] = s->img.adr[i];
			buffer[1] = s->img.adr[i] >> 8;
			buffer[2] = s->img.adr[i] >> 16;
			buffer[3] = 0;
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * s->win.x;
	}
}

void	ft_binfo(t_all *s, int fd)
{
	int		n;
	char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = 0;
	header[0] = 40;
	n = s->win.x;
	header[4] = n;
	header[5] = n >> 8;
	header[6] = n >> 16;
	header[7] = n >> 24;
	n = s->win.y;
	header[8] = n;
	header[9] = n >> 8;
	header[10] = n >> 16;
	header[11] = n >> 24;
	header[12] = 1;
	header[14] = 32;
	write(fd, header, 40);
}

void	ft_bfile(t_all *s, int fd)
{
	int		n;
	char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = 0;
	header[0] = 66;
	header[1] = 77;
	n = s->win.x * s->win.y * 4 + 54;
	header[2] = n;
	header[3] = n >> 8;
	header[4] = n >> 16;
	header[5] = n >> 24;
	header[10] = 54;
	write(fd, header, 14);
}

void	ft_bitmap(t_all *s)
{
	int		fd;

	ft_draw(s, 1);
	fd = creat("bitmap.bmp", S_IRWXU);
	ft_bfile(s, fd);
	ft_binfo(s, fd);
	ft_bdata(s, fd);
	close(fd);
	free(s->img.ptr);
	free(s->img.adr);
	ft_close(s, 0);
}
