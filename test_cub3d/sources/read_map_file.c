#include "cub3d.h"

int		check_map(t_game *gm)
{
	int		i;
	int		j;

	i = -1;
	while (++i < gm->map.y)
	{
		j = -1;
		while (++j < gm->map.x)
		{
			if (i == 0 && gm->map.array[i][j] != '1' && gm->map.array[i][j] != ' ')
				return (-1);
			if (i == gm->map.y - 1 && gm->map.array[i][j] != '1' && gm->map.array[i][j] != ' ')
				return (-1);
			if (j == 0 && gm->map.array[i][j] != '1' && gm->map.array[i][j] != ' ')
				return (-1);
			if (j == gm->map.x - 1 && gm->map.array[i][j] != '1' && gm->map.array[i][j] != ' ')
				return (-1);
			if (i > 0 && i < gm->map.y - 1 && j > 0 && j < gm->map.x - 1 &&
				gm->map.array[i][j] != ' ' && gm->map.array[i][j] != '1')
				if (gm->map.array[i - 1][j] == ' ' || gm->map.array[i + 1][j] == ' ' ||
					gm->map.array[i][j - 1] == ' ' || gm->map.array[i][j + 1] == ' ')
					return (-1);
		}
	}
	return (1);
}

int		check_data(t_game *gm)
{
	if (check_map(gm) == -1)
		return (print_error(-3));
	if (gm->error.pos_num != 1)
		return (print_error(-9));
	if (gm->win.x <= 0 || gm->win.y <= 0)
		return (print_error(-8));
	if ((gm->txr.north == 0 || gm->txr.south == 0 || gm->txr.east == 0) ||
		(gm->txr.west == 0 || gm->txr.sprt == 0))
		return (print_error(-5));
	if (gm->txr.up == NO_COLOR || gm->txr.down == NO_COLOR)
		return (print_error(-4));
	return (1);
}

int fill_map(t_game *gm) {
	char	*temp;
	int		i;

	i = 0;
	while (i < gm->map.y)
	{
		while ((int)ft_strlen(gm->map.array[i]) < gm->map.x)
		{
			temp = gm->map.array[i];
			gm->map.array[i] = ft_strjoin(gm->map.array[i], " ");
			free(temp);
			if (gm->map.array[i] == 0)
				return (print_error(-6));
		}
		i++;
	}
	return (1);
}

int		parse_line(t_game *gm, char *line)
{
	int		i;

	i = 0;
	skip_space(line, &i);
	if ((line[i] == '1' || gm->error.map_mode == 1) && line[i] != '\0')
		gm->error.num = parse_map(gm, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		gm->error.num = parse_resolution(gm, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		gm->error.num = parse_txr_path(gm, &gm->txr.north, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		gm->error.num = parse_txr_path(gm, &gm->txr.south, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		gm->error.num = parse_txr_path(gm, &gm->txr.west, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		gm->error.num = parse_txr_path(gm, &gm->txr.east, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		gm->error.num = parse_txr_path(gm, &gm->txr.sprt, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		gm->error.num = parse_colors(&gm->txr.down, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		gm->error.num = parse_colors(&gm->txr.up, line, &i);
	if (skip_space(line, &i) && gm->error.num == 0 && line[i] != '\0')
		return (print_error(-7));
	return (gm->error.num < 0 ? print_error(gm->error.num) : 0);
}

int		read_map_file(t_game *gm, char *map)
{
	char	*line;
	int		fd;
	int		rslt;

	rslt = 1;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (print_error(-1));
	while (rslt == 1)
	{
		rslt = get_next_line(fd, &line);
		if (parse_line(gm, line) == -1)
			rslt = -1;
		free(line);
	}
	close(fd);
	if (rslt == -1 || fill_map(gm) == -1)
		return (-1);
	parse_position(gm);
	parse_sprites(gm);
	rslt = check_data(gm);
	return (rslt);
}