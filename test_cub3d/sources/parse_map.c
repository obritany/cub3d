#include "cub3d.h"

int		ft_xpm(t_all *s, unsigned int **adr, char *file)
{
	void	*img;
	int		tab[5];

	if (ft_strncmp(ft_strrchr(file, '.'), ".xpm", 4))
		return (-1);
	img = mlx_xpm_file_to_image(s->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == 0 || tab[0] != XPM_SIZE || tab[1] != XPM_SIZE)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		ft_texture(t_all *s, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != 0)
		return (-5);
	(*i) += 2;
	ft_skip_sp(line, i);
	j = *i;
	while (line[*i] && line[*i] != ' ')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-6);
	*i = j;
	j = 0;
	while (line[*i] && line[*i] != ' ')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = ft_xpm(s, adr, file);
	free(file);
	return (j == -1 ? -5 : 0);
}

char	*ft_slab(t_all *s, char *line, int *i)
{
	int		len;
	char	*slab;
	int		j;

	len = ft_strlen(line);
	s->map.x = (len > s->map.x) ? len : s->map.x;
	if (!(slab = malloc(sizeof(char) * (len + 1))))
		return (0);
	j = 0;
	while (line[*i])
	{
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == '2' ||
			line[*i] == 'N' || line[*i] == 'S' ||
			line[*i] == 'W' || line[*i] == 'E' ||
			line[*i] == ' ')
			slab[j++] = line[*i];
		else
			return (0);
		if (line[*i] == '2')
			s->map.spr++;
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int		ft_parse_map(t_all *s, char *line, int *i)
{
	char	**temp;
	int		j;

	*i = 0;
	s->err.m = 1;
	if (!(temp = malloc(sizeof(char *) * (s->map.y + 2))))
		return (-6);
	j = 0;
	while (j < s->map.y)
	{
		temp[j] = s->map.tab[j];
		j++;
	}
	if ((temp[s->map.y] = ft_slab(s, line, i)) == 0)
	{
		free(temp);
		return (-3);
	}
	temp[s->map.y + 1] = 0;
	if (s->map.y != 0)
		free(s->map.tab);
	s->map.tab = temp;
	s->map.y++;
	return (0);
}
