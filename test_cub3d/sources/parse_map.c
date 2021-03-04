#include "cub3d.h"

int		parse_xpm(t_game *gm, unsigned int **txr_adr, char *path)
{
	void	*img;
	int		info[5];

	if (ft_strncmp(ft_strrchr(path, '.'), ".xpm", 4))
		return (-1);
	img = mlx_xpm_file_to_image(gm->mlx.ptr, path, &info[0], &info[1]);
	if (img == 0 || info[0] != XPM_SIZE || info[1] != XPM_SIZE)
		return (-1);
	*txr_adr = (unsigned int *)mlx_get_data_addr(img, &info[2], &info[3], &info[4]);
	free(img);
	return (0);
}

int		parse_txr_path(t_game *gm, unsigned int **txr_adr, char *line, int *i)
{
	char	*path;
	int		j;

	if (*txr_adr != 0)
		return (-5);
	(*i) += 2;
	skip_space(line, i);
	j = *i;
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	if (!(path = malloc(sizeof(char) * (*i - j + 1))))
		return (-6);
	*i = j;
	j = 0;
	while (line[*i] && line[*i] != ' ')
		path[j++] = line[(*i)++];
	path[j] = '\0';
	j = parse_xpm(gm, txr_adr, path);
	free(path);
	return (j == -1 ? -5 : 0);
}

char	*parse_map_line(t_game *gm, char *line, int *i)
{
	int		len;
	char	*map_line;
	int		j;

	len = ft_strlen(line);
	gm->map.x = (len > gm->map.x) ? len : gm->map.x;
	if (!(map_line = malloc(sizeof(char) * (len + 1))))
		return (0);
	j = 0;
	while (line[*i])
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == '2' ||
			line[*i] == 'N' || line[*i] == 'S' ||
			line[*i] == 'W' || line[*i] == 'E' ||
			line[*i] == ' ')
			map_line[j++] = line[*i];
		else
			return (0);
		if (line[*i] == '2')
			gm->map.sprt_num++;
		(*i)++;
	}
	map_line[j] = '\0';
	return (map_line);
}

int		parse_map(t_game *gm, char *line, int *i)
{
	char	**temp;
	int		j;

	*i = 0;
	j = 0;
	gm->error.map_mode = 1;
	if (!(temp = malloc(sizeof(char *) * (gm->map.y + 2))))
		return (-6);
	while (j < gm->map.y)
	{
		temp[j] = gm->map.array[j];
		j++;
	}
	if ((temp[gm->map.y] = parse_map_line(gm, line, i)) == 0)
	{
		free(temp);
		return (-3);
	}
	temp[gm->map.y + 1] = 0;
	if (gm->map.y != 0)
		free(gm->map.array);
	gm->map.array = temp;
	gm->map.y++;
	return (0);
}
