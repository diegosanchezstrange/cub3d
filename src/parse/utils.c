/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:35:30 by dsanchez          #+#    #+#             */
/*   Updated: 2022/07/23 18:37:01 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 * Check if the files for the textures exist and save the path
 * on the cub structure.
 */
int	check_direction_path(t_cub *cub, char **split, int *num)
{
	int		fd;
	char	*path;

	if (ft_splitlen(split) != 2)
		return (0);
	path = ft_strdup(split[1]);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	if (!ft_strncmp(split[0], "NO", 2))
		cub->NO_path = path;
	else if (!ft_strncmp(split[0], "SO", 2))
		cub->SO_path = path;
	else if (!ft_strncmp(split[0], "WE", 2))
		cub->WE_path = path;
	else if (!ft_strncmp(split[0], "EA", 2))
		cub->EA_path = path;
	ft_free_split(split);
	*num += 1;
	return (1);
}

/*
 * Check if the colors for the floor and cealing are valid 
 * and save them on the cub structure.
 */
int	check_color_code(t_cub *cub, char **split, int *num)
{
	char	**colors;
	int		i;
	int		n;

	i = 0;
	if (ft_splitlen(split) != 2)
		return (0);
	colors = ft_split(split[1], ',');
	if (ft_splitlen(colors) != 3)
		return (0);
	while (i < 3)
	{
		n = ft_atoi(colors[i]);
		if (n < 0 | n > 255)
			return (0);
		else if (!ft_strncmp(split[0], "F", 1))
			cub->F_color[i] = n;
		else if (!ft_strncmp(split[0], "C", 1))
			cub->C_color[i] = n;
		i++;
	}
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
	while (split[n])
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
