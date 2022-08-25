/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:42:38 by dsanchez          #+#    #+#             */
/*   Updated: 2022/08/25 21:07:47 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_texnum(t_render *params)
{
	if (params->side == 0)
	{
		if (params->ray_dir.x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (params->ray_dir.y > 0)
			return (NO);
		else
			return (SO);
	}
}

void	ft_rotate(t_cub *prog, t_render *params)
{
	double	old_dir_x;
	double	old_plane_x;
	double	s;

	old_dir_x = params->dir.x;
	old_plane_x = params->plane.x;
	s = 0.00005;
	if (prog->keys.left == 1)
	{
		params->dir.x = (params->dir.x * cos(-s)) - (params->dir.y * sin(-s));
		params->dir.y = (old_dir_x * sin(-s)) + (params->dir.y * cos(-s));
		params->plane.x
			= (params->plane.x * cos(-s)) - (params->plane.y * sin(-s));
		params->plane.y = (old_plane_x * sin(-s)) + (params->plane.y * cos(-s));
	}
	else if (prog->keys.right == 1)
	{
		params->dir.x = (params->dir.x * cos(s)) - (params->dir.y * sin(s));
		params->dir.y = (old_dir_x * sin(s)) + (params->dir.y * cos(s));
		params->plane.x
			= (params->plane.x * cos(s)) - (params->plane.y * sin(s));
		params->plane.y = (old_plane_x * sin(s)) + (params->plane.y * cos(s));
	}	
}

void	ft_move_side(t_cub *prog, t_render *params)
{
	t_point	pos;
	double	s;

	pos.x = params->pos.x;
	pos.y = params->pos.y;
	s = 0.00008;
	//if (prog->map[(int)pos.y][(int)pos.x] == '1')
		//return ;
	if (prog->keys.d == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x + params->plane.x * s)] != '1')
			prog->pos.x += params->plane.x * s;
		if (prog->map[(int)(pos.y + params->plane.y * s)][(int)pos.x] != '1')
			prog->pos.y += params->plane.y * s;
	}		
	else if (prog->keys.a == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x - params->plane.x * s)] != '1')
			prog->pos.x -= params->plane.x * s;
		if (prog->map[(int)(pos.y - params->plane.y * s)][(int)(pos.x)] != '1')
			prog->pos.y -= params->plane.y * s;
	}	
}

void	ft_move(t_cub *prog, t_render *params)
{
	t_point	pos;
	double	s;

	pos.x = params->pos.x;
	pos.y = params->pos.y;
	s = 0.00008;
	//if (prog->map[(int)pos.y][(int)pos.x] == '1')
		//return ;
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
	ft_move_side(prog, params);
}
