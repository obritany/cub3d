#include "cub3d.h"

int		ft_mapcheck(t_all *s)
{
	int		i;
	int		j;

	i = 0;
	while (i < s->map.y)
	{
		j = 0;
		while (j < s->map.x)
		{
			if (i == 0 && s->map.tab[i][j] != '1' && s->map.tab[i][j] != ' ')
				return (-1);
			if (i == s->map.y - 1 && s->map.tab[i][j] != '1' && s->map.tab[i][j] != ' ')
				return (-1);
			if (j == 0 && s->map.tab[i][j] != '1' && s->map.tab[i][j] != ' ')
				return (-1);
			if (j == s->map.x - 1 && s->map.tab[i][j] != '1' && s->map.tab[i][j] != ' ')
				return (-1);

			if (i > 0 && i < s->map.y - 1 && j > 0 && j < s->map.x - 1 &&
				s->map.tab[i][j] != ' ' && s->map.tab[i][j] != '1')
				if (s->map.tab[i - 1][j] == ' ' || s->map.tab[i + 1][j] == ' ' ||
					s->map.tab[i][j - 1] == ' ' || s->map.tab[i][j + 1] == ' ')
					return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_all *s)
{
	if (s->win.x <= 0 || s->win.y <= 0)
		return (ft_error(-8));
	if ((s->tex.n == 0 || s->tex.s == 0 || s->tex.e == 0) ||
		(s->tex.w == 0 || s->tex.i == 0))
		return (ft_error(-5));
	if (s->tex.c == NO_COLOR || s->tex.f == NO_COLOR)
		return (ft_error(-4));
	if (ft_mapcheck(s) == -1)
		return (ft_error(-3));
	if (s->err.p == 0)
		return (ft_error(-9));
	if (s->err.p > 1)
		return (ft_error(-9));
	return (1);
}
