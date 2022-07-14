#ifndef FDF_H
# define FDF_H
# include <libft.h>

typedef struct	s_cub
{
	void	*mlx;
	void	*win;
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	char	*f_color;
	char	*c_color;
}				t_cub;

// parse/utils.c
int	is_valid_param(t_cub *cub, char *line, int *num);

// parse/parse.c
int	ft_parse_file(char *filename, t_cub *cub);

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

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
