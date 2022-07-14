#include <cub3d.h>
#include <fcntl.h>

int	ft_parse_info()
{
}

int	ft_parse_line(char *line, t_cub *cub, int *num)
{
	char	**split;

	split = ft_split(line, ' ');
	if (ft_strlen(split) < 2 && *num < 6)
		return (1);
	return (0);
}

void	ft_parse_file(char *filename, t_cub *cub)
{
	int		fd;
	int		num;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		ft_printf(line);
		if (ft_strlen(line) > 1)
			ft_parse_line(line, cub, &num);
		line = get_next_line(fd);
	}
}
