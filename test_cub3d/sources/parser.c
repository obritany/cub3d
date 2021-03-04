#include "cub3d.h"

void	parse_position(t_game *gm)
{
	char	chr;
	int		i;
	int		j;

	i = -1;
	while (++i < gm->map.y)
	{
		j = -1;
		while (++j < gm->map.x)
		{
			chr = gm->map.array[i][j];
			if (chr != 'N' && chr != 'E' && chr != 'S' && chr != 'W')
				continue ;
			gm->pos.y = (double)i + 0.5;
			gm->pos.x = (double)j + 0.5;
			gm->dir.x = (chr == 'E' || chr == 'W') ? 1 : 0;
			gm->dir.x *= (chr == 'W') ? -1 : 1;
			gm->dir.y = (chr == 'S' || chr == 'N') ? 1 : 0;
			gm->dir.y *= (chr == 'N') ? -1 : 1;
			gm->error.pos_num++;
		}
	}
}

int		parse_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NO_COLOR)
		return (-4);
	(*i)++;
	r = ft_atoi_line(line, i);
	(*i)++;
	g = ft_atoi_line(line, i);
	(*i)++;
	b = ft_atoi_line(line, i);
	skip_space(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-4);
	*color = (r << 16) + (g << 8) + b;
	return (0);
}

int		parse_resolution(t_game *gm, char *line, int *i)
{
	if (gm->win.x != 0 || gm->win.y != 0)
		return (-2);
	(*i)++;
	gm->win.x = ft_atoi_line(line, i);
	gm->win.y = ft_atoi_line(line, i);
	gm->win.x = (gm->win.x > 2560) ? 2560 : gm->win.x;
	gm->win.y = (gm->win.y > 1400) ? 1400 : gm->win.y;
	skip_space(line, i);
	if (gm->win.x <= 0 || gm->win.y <= 0 || line[*i] != '\0')
		return (-2);
	return (0);
}

int		parse_sprites(t_game *gm)
{
	int	i;
	int	j;
	int	k;

	if (!(gm->sprt = malloc(sizeof(t_sprt) * gm->map.sprt_num)))
		return (-1);
	i = 0;
	j = 0;
	while (j < gm->map.y)
	{
		k = 0;
		while (k < gm->map.x)
		{
			if (gm->map.array[j][k] == '2')
			{
				gm->sprt[i].y = (double)j + 0.5;
				gm->sprt[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}
