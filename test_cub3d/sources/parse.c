#include "cub3d.h"

int ft_fill_map(t_all *s) {
	char	*temp;
	int		i;

	i = 0;
	while (i < s->map.y)
	{
		while (ft_strlen(s->map.tab[i]) < s->map.x)
		{
			temp = s->map.tab[i];
			s->map.tab[i] = ft_strjoin(s->map.tab[i], " ");
			free(temp);
			if (s->map.tab[i] == 0)
				return (ft_error(-6));
		}
		i++;
	}
	return (1);
}

int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_skip_sp(line, &i);
	if ((line[i] == '1' || s->err.m == 1) && line[i] != '\0')
		s->err.n = ft_parse_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_parse_resolution(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		s->err.n = ft_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_parse_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_parse_colors(&s->tex.c, line, &i);
	if (ft_skip_sp(line, &i) && s->err.n == 0 && line[i] != '\0')
		return (ft_error(-7));
	return (s->err.n < 0 ? ft_error(s->err.n) : 0);
}

int		ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_error(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ft_fill_map(s) == -1)
		return (-1);
	ft_parse_position(s);
	ft_parse_sprites(s);
	return (ft_parcheck(s));
}