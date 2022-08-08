/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:38:02 by dsanchez          #+#    #+#             */
/*   Updated: 2022/08/01 21:21:09 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_check_valid_map_line(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NSEW", line[i]))
		{
			ft_printf("MAP ERROR: %c is not a valid char\n", line[i]);
			return (0);
		}
		else if (ft_strchr("NSEW", line[i]) && cub->starting_way != 0)
		{
			ft_printf("MAP ERROR: Only one starting point valid.\n");
			return (0);
		}
		else if (ft_strchr("NSEW", line[i]) && cub->starting_way == 0)
		{
			cub->starting_way = line[i];
			cub->pos.x = (double)i;
			cub->pos.y = (double)cub->map_h;
		}
		i++;
	}
	return (1);
}

int	ft_parse_map(t_cub *cub, char *line)
{
	int		i;
	size_t	w;
	char	**new_map;

	i = -1;
	if (!ft_check_valid_map_line(cub, line))
		return (0);
	w = ft_strlen(line);
	cub->map_h++;
	if (w > cub->map_w)
		cub->map_w = w;
	new_map = ft_calloc(cub->map_h + 1, sizeof(char *));
	while (cub->map[++i])
		new_map[i] = cub->map[i];
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(cub->map);
	cub->map = new_map;
	return (1);
}

int	ft_parse_line(char *line, t_cub *cub, int *num)
{
	int	ret;

	if (ft_strlen(line) <= 1)
		ret = *num != -1;
	else if (*num < 6 && *num != -1)
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
	num = 0;
	while (line)
	{
		if (!ft_parse_line(line, cub, &num))
		{
			free(line);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	ft_resize_map(cub);
	return (ft_check_closed(cub));
}
