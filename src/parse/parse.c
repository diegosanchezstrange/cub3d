#include <cub3d.h>
#include <fcntl.h>

int	ft_parse_map()
{
	return (0);
}

int	ft_parse_line(char *line, t_cub *cub, int *num)
{
	(void) cub;
	if (*num < 6)
		return (is_valid_param(cub, line, num));
	else 
		return (ft_parse_map());
}

int	ft_parse_file(char *filename, t_cub *cub)
{
	int		fd;
	int		num;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) > 1)
		{
			if (!ft_parse_line(line, cub, &num))
			{
				ft_printf("Error in : %s", line);
				return (0);
			}
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
