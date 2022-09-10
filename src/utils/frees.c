/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:37:06 by dsanchez          #+#    #+#             */
/*   Updated: 2022/09/10 14:19:23 by dsanchez         ###   ########.fr       */
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
	free(cub->no_path);
	free(cub->so_path);
	free(cub->we_path);
	free(cub->ea_path);
	free(cub->params);
}

void	ft_free_all(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_image(cub->mlx, cub->tex[0].img.img);
	mlx_destroy_image(cub->mlx, cub->tex[1].img.img);
	mlx_destroy_image(cub->mlx, cub->tex[2].img.img);
	mlx_destroy_image(cub->mlx, cub->tex[3].img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	ft_free_cub(cub);
}
