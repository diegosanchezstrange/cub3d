#include <cub3d.h>
#include <fcntl.h>

int	ft_check_space_y(t_cub *cub, size_t y, size_t x)
{
	size_t	i;

	i = y;
	while (cub->map[i])
	{
		if (cub->map[i][x] == '1')
			break ;
		else if (cub->map[i][x] != ' ')
			return (0);
		i++;
	}
	i = y;
	while (cub->map[i])
	{
		if (cub->map[i][x] == '1')
			break ;
		else if (cub->map[i][x] != ' ')
			return (0);
		if (i == 0)
			break;
		i--;
	}
	return (1);
}

int	ft_check_space_x(t_cub *cub, size_t y, size_t x)
{
	size_t	j;

	j = x;
	while (j < cub->map_w)
	{
		if (cub->map[y][j] == '1')
			break ;
		else if (cub->map[y][j] != ' ')
			return (0);
		j++;
	}
	j = x;
	while (j)
	{
		if (cub->map[y][j] == '1')
			break ;
		else if (cub->map[y][j] != ' ')
			return (0);
		if (j == 0)
			break;
		j--;
	}
	return (1);
}

int	ft_check_closed(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if ((i == 0 || j == 0 || i == cub->map_h || j == cub->map_w)
					&& !(cub->map[i][j] == '1' || cub->map[i][j] == ' '))
				return (0);
			if (cub->map[i][j] == ' ')
			{
				if (!ft_check_space_y(cub, i, j) || !ft_check_space_x(cub, i, j) )
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void ft_resize_map(t_cub *cub)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = -1;
	while (cub->map[++i])
	{
		if (ft_strlen(cub->map[i]) == cub->map_w)
			continue ;
		tmp = ft_calloc(cub->map_w + 1, sizeof(char));
		j = -1;
		while (cub->map[i][++j])
			tmp[j] = cub->map[i][j];
		while (j < cub->map_w)
			tmp[j++] = ' ';
		tmp[j] = 0;
		free(cub->map[i]);
		cub->map[i] = tmp;
	}
}

int	ft_parse_map(t_cub *cub, char *line)
{
	int		i;
	size_t	w;
	char	**newMap;

	i = 0;
	w = ft_strlen(line);
	while (line[i])
	{
		if (!ft_strchr("10 NSEW", line[i++]))
			return (0);
	}
	cub->map_h++;
	if (w > cub->map_w)
		cub->map_w = w;
	newMap = ft_calloc(cub->map_h + 1, sizeof(char *));
	i = -1;
	while (cub->map[++i])
		newMap[i] = cub->map[i];
	newMap[i] = line;
	newMap[i + 1] = NULL;
	free(cub->map);
	cub->map = newMap;
	return (1);
}

int	ft_parse_line(char *line, t_cub *cub, int *num)
{
	int	ret;
	
	if (*num < 6 && *num != -1)
		ret = is_valid_param(cub, line, num);
	else 
	{
		*num = -1;
		ret = ft_parse_map(cub, line);
	}
	if (ret == 0)
		ft_printf("Error in : |%s|\n", line);
	return (ret);
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
				return (0);
		}
		else if (num == -1)
			return (0);
		line = get_next_line(fd);
	}
	close(fd);
	ft_resize_map(cub);
	return (ft_check_closed(cub));
}
