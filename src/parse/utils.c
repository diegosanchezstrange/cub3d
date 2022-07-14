#include <cub3d.h>

int	check_direction_path(t_cub *cub, char **split, int *num)
{
	(void) split;
	(void) cub;
	*num += 1;
	return (1);
}

int	check_color_code(t_cub *cub, char **split, int *num)
{
	(void) split;
	(void) cub;
	*num += 1;
	return (1);
}

int	is_valid_param(t_cub *cub, char *line, int *num)
{
	int		n;
	char	*first;
	size_t	l;
	char	**split;

	n = 0;
	split = ft_split(line, ' ');
	while(split[n])
		n++;
	first = split[0];
	l = ft_strlen(first);
	if (!ft_strncmp(first, "NO", l) || !ft_strncmp(first, "SO", l) 
			|| !ft_strncmp(first, "WE", l) || !ft_strncmp(first, "EA", l))
		return (check_direction_path(cub, split, num));
	if (!ft_strncmp(first, "F", l) || !ft_strncmp(first, "C", l))
		return (check_color_code(cub, split, num));
	return (0);
}
