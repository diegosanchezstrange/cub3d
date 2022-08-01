#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <fcntl.h>
# include <mlx.h>

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct s_point{
	double	x;
	double	y;
	double	mod;
	double	angle;
}				t_point;
typedef struct	s_cub
{
	void	*mlx;
	void	*win;
	t_data	img;
	char	*NO_path;
	char	*SO_path;
	char	*WE_path;
	char	*EA_path;
	int		F_color[3];
	int		C_color[3];
	char	**map;
	char	starting_way;
	t_point	pos;
	t_point	dir;
	t_point	plane;
	size_t	map_w;
	size_t	map_h;
	int		move; // 0 right rotation, 1 left rotation
}				t_cub;

//	utils/splits.c
size_t	ft_splitlen(char **split);
void	ft_free_split(char **split);
// parse/utils.c
int		is_valid_param(t_cub *cub, char *line, int *num);
// parse/parse_map.c
int		ft_check_closed(t_cub *cub);
void initialize_pos(t_cub *prog);
void ft_move(t_cub *prog);
void ft_rotate(t_cub *prog);
void	ft_resize_map(t_cub *cub);
// parse/parse.c
int		ft_parse_file(char *filename, t_cub *cub);
void ft_start(t_cub *prog);
void	plot_line(t_point p1, t_point p2, t_data img, int color);
double	ft_abs(double num);

# define WALL 0xCCFFCC
# define WALL_2 0x66FF66
# define W 640
# define H 480

# define X_OFFSET 20
# define Y_OFFSET 20

# ifdef OSX
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_P 35
#  define KEY_PLUS 69
#  define KEY_C 8
# elif LINUX
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_P 112
#  define KEY_PLUS 43
#  define KEY_C 99
# else
#  define LINUX
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_P 112
#  define KEY_PLUS 61
#  define KEY_C 99
# endif

#endif
