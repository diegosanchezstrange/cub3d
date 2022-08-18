/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:42:38 by dsanchez          #+#    #+#             */
/*   Updated: 2022/08/18 18:16:34 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void ft_rotate(t_cub *prog, t_render *params)
{
	double	oldDir_x;
	double	oldPlane_x;
	double 	s;

	oldDir_x = params->dir.x;
	oldPlane_x = params->plane.x;
	s = 0.00005;
	if (prog->keys.left == 1)
	{
		params->dir.x = (params->dir.x * cos(-s)) - (params->dir.y * sin(-s));
		params->dir.y = (oldDir_x * sin(-s)) + (params->dir.y * cos(-s));
		params->plane.x = (params->plane.x * cos(-s)) - (params->plane.y * sin(-s));
		params->plane.y = (oldPlane_x * sin(-s)) + (params->plane.y * cos(-s));
	}
	else if (prog->keys.right == 1)
	{
		params->dir.x = (params->dir.x * cos(s)) - (params->dir.y * sin(s));
		params->dir.y = (oldDir_x * sin(s)) + (params->dir.y * cos(s));
		params->plane.x = (params->plane.x * cos(s)) - (params->plane.y * sin(s));
		params->plane.y = (oldPlane_x * sin(s)) + (params->plane.y * cos(s));
	}	
}

/*int	ft_round_x(double num, t_render *params)
{
	if (params->dir.x > 0)
	{
		if (0.8f < (num - floor(num)))
			return ((int)ceil(num));
	}
	else
	{
		if (0.1f < (num - floor(num)))
			return ((int)(num) - 1);
	}
	return ((int)num);
}

int	ft_round_y(double num, t_render *params)
{
	if (params->dir.y > 0)
	{
		if (0.8f < (num - floor(num)))
			return ((int)ceil(num));
	}
	else
	{
		if (0.1f < (num - floor(num)))
			return ((int)(num) - 1);
	}
	return ((int)num);

}*/

void ft_move(t_cub *prog, t_render *params)
{
	t_point	pos;
	double	s;

	pos.x = params->pos.x;
	pos.y = params->pos.y;
	s = 0.025;
	if (prog->map[(int)pos.y][(int)pos.x] == '1')
		return ;
	if (prog->keys.w == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x + params->dir.x * s)] != '1')
			prog->pos.x += params->dir.x * s;
		if (prog->map[(int)(pos.y + params->dir.y * s)][(int)pos.x] != '1')
			prog->pos.y += params->dir.y * s;
	}		
	else if (prog->keys.s == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x - params->dir.x * s)] != '1')
			prog->pos.x -= params->dir.x * s;
		if (prog->map[(int)(pos.y - params->dir.y * s)][(int)(pos.x)] != '1')
			prog->pos.y -= params->dir.y * s;
	}	
}
