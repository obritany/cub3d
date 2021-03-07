/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:11:30 by obritany          #+#    #+#             */
/*   Updated: 2021/03/06 16:17:21 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libmlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define XPM 64
# define NO_COLOR 0xFF000000

# define ESC	53
# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124

# define FOV		60.0
# define MV_SPD		17.5
# define TRN_ANG	0.10

typedef struct	s_win
{
	void	*ptr;
	int		x;
	int		y;
}				t_win;

typedef struct	s_mlx
{
	void	*ptr;
}				t_mlx;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
}				t_img;

typedef struct	s_map
{
	char	**arr;
	int		x;
	int		y;
	int		sprt_num;
}				t_map;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_error
{
	int	num;
	int	map_mode;
	int	pos_num;
}				t_error;

typedef struct	s_txr
{
	unsigned int	*north;
	unsigned int	*south;
	unsigned int	*east;
	unsigned int	*west;
	unsigned int	*sprt;
	unsigned int	up;
	unsigned int	down;
}				t_txr;

typedef struct	s_sprt
{
	double	x;
	double	y;
	double	d;
}				t_sprt;

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
	double	e;
	double	s;
}				t_ray;

typedef struct	s_hit
{
	double	x;
	double	y;
	double	d;
}				t_hit;

typedef struct	s_raycast
{
	double	x;
	double	y;
	double	d;
}				t_raycast;

typedef struct	s_game
{
	t_mlx		mlx;
	t_win		win;
	t_img		img;
	t_error		error;
	t_map		map;
	t_txr		txr;
	t_pos		pos;
	t_dir		dir;
	t_ray		ray;
	t_hit		hit;
	t_sprt		*sprt;
	t_raycast	*raycast;
}				t_game;

void			refresh_frame(t_game *gm, int mode);
int				read_map_file(t_game *gm, char *map);
int				parse_map(t_game *gm, char *line, int *i);
int				parse_txr_path(t_game *gm, unsigned int **txr_adr,
								char *line, int *i);
int				parse_sprites(t_game *gm);
void			parse_position(t_game *gm);
int				parse_colors(unsigned int *color, char *line, int *i);
int				parse_resolution(t_game *gm, char *line, int *i);
int				check_data(t_game *gm);
int				control(int key, t_game *gm);
int				close_app(t_game *gm, int window);
int				draw_image(t_game *gm);
void			save_ray(t_game *gm);
int				get_true_height(t_game *gm);
void			draw_column(t_game *gm);
void			add_sprites(t_game *gm);
void			save_bmp(t_game *gm);
int				ft_atoi_line(char *line, int *i);
int				skip_space(char *line, int *i);
int				print_error(int error);

#endif
