#include "cub3d.h"

void	ft_parse_position(t_all *s)
{
	char	chr;
	int		i;
	int		j;

	i = -1;
	while (++i < s->map.y)
	{
		j = -1;
		while (++j < s->map.x)
		{
			chr = s->map.tab[i][j];
			if (chr != 'N' && chr != 'E' && chr != 'S' && chr != 'W')
				continue ;
			s->pos.y = (double)i + 0.5;
			s->pos.x = (double)j + 0.5;
			s->dir.x = (chr == 'E' || chr == 'W') ? 1 : 0;
			s->dir.x *= (chr == 'W') ? -1 : 1;
			s->dir.y = (chr == 'S' || chr == 'N') ? 1 : 0;
			s->dir.y *= (chr == 'N') ? -1 : 1;
			s->err.p++;
		}
	}
}

int		ft_parse_colors(unsigned int *color, char *line, int *i)
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
	ft_skip_sp(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-4);
	*color = (r << 16) + (g << 8) + b;
	return (0);
}

int		ft_parse_resolution(t_all *s, char *line, int *i)
{
	if (s->win.x != 0 || s->win.y != 0)
		return (-2);
	(*i)++;
	s->win.x = ft_atoi_line(line, i);
	s->win.y = ft_atoi_line(line, i);
	s->win.x = (s->win.x > 2560) ? 2560 : s->win.x;
	s->win.y = (s->win.y > 1400) ? 1400 : s->win.y;
	ft_skip_sp(line, i);
	if (s->win.x <= 0 || s->win.y <= 0 || line[*i] != '\0')
		return (-2);
	return (0);
}

int		ft_parse_sprites(t_all *s)
{
	int	i;
	int	j;
	int	k;

	if (!(s->spr = malloc(sizeof(t_spr) * s->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				s->spr[i].y = (double)j + 0.5;
				s->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}
