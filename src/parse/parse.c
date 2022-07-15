#include <cub3d.h>
#include <fcntl.h>

int	ft_parse_map(t_cub *cub, char *line, int *num)
{
	(void) line;
	ft_printf("NO : %s\n", cub->NO_path);
	ft_printf("SO : %s\n", cub->SO_path);
	ft_printf("WE : %s\n", cub->WE_path);
	ft_printf("EA : %s\n", cub->EA_path);
	ft_printf("F : %d,%d,%d\n", cub->F_color[0], cub->F_color[1], cub->F_color[2]);
	ft_printf("C : %d,%d,%d\n", cub->C_color[0], cub->C_color[1], cub->C_color[2]);
	*num += 1;
	return (0);
}

int	ft_parse_line(char *line, t_cub *cub, int *num)
{
	(void) cub;
	if (*num < 6)
		return (is_valid_param(cub, line, num));
	else 
		return (ft_parse_map(cub, line, num));
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
				ft_printf("Error in : %s\n", line);
				return (0);
			}
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
