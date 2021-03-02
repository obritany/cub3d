#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_opengl/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

#include <stdio.h>

# define NO_COLOR 0xFF000000
# define XPM_SIZE 64

# define ESC	53
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124

# define FOV	60.0
# define SPEED	17.5
# define TURN	0.10

typedef struct	s_mlx
{
	void	*ptr;
}				t_mlx;

typedef struct	s_win
{
	void	*ptr;
	int		x;
	int		y;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
}				t_img;

typedef struct	s_err
{
	int	n;
	int	m;
	int	p;
}				t_err;

typedef struct	s_map
{
	char	**tab;
	int		x;
	int		y;
	int		spr;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_dir
{
	double	x;
	double	y;
	double	a;
}				t_dir;

typedef struct	s_ray
{
	double	x;
	double	y;
	int		i;
	double	v;
	double	w;
}				t_ray;

typedef struct	s_hit
{
	double	x;
	double	y;
	double	d;
}				t_hit;

typedef struct	s_spr
{
	double	x;
	double	y;
	double	d;
}				t_spr;

typedef struct	s_stk
{
	double	x;
	double	y;
	double	d;
}				t_stk;

typedef struct	s_all
{
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;
	t_map	map;
	t_tex	tex;
	t_pos	pos;
	t_dir	dir;
	t_ray	ray;
	t_hit	hit;
	t_spr	*spr;
	t_stk	*stk;
}				t_all;

void			ft_draw(t_all *s, int mode);

int				ft_parse(t_all *s, char *cub);

int				ft_parse_map(t_all *s, char *line, int *i);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);

int				ft_parse_sprites(t_all *s);
void			ft_parse_position(t_all *s);
int				ft_parse_colors(unsigned int *color, char *line, int *i);
int				ft_parse_resolution(t_all *s, char *line, int *i);

int				ft_parcheck(t_all *s);

int				ft_key(int key, t_all *s);
int				ft_close(t_all *s, int win);

void			ft_draw_image(t_all *s);

void			ft_save_ray(t_all *s);
int				ft_true_height(t_all *s);
void			ft_draw_column(t_all *s);

void			ft_add_sprites(t_all *s);

void			ft_bitmap(t_all *s);

int				ft_atoi_line(char *line, int *i);
int				ft_skip_sp(char *line, int *i);
int				ft_error(int error);

#endif
