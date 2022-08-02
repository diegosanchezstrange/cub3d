/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:37:06 by dsanchez          #+#    #+#             */
/*   Updated: 2022/07/23 18:37:09 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

size_t	ft_splitlen(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_cub(t_cub *cub)
{
	ft_free_split(cub->map);
	free(cub->NO_path);
	free(cub->SO_path);
	free(cub->WE_path);
	free(cub->EA_path);
}

void ft_free_all(t_cub *cub)
{
	ft_free_cub(cub);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_image(cub->mlx, cub->img.img);
}
