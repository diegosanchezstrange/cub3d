#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double	ft_abs(double num)
{
	if (num > 0)
		return num;
	return num*-1;
}

void ft_rotate(t_cub *prog, t_render *params)
{
	double	oldDir_x;
	double	oldPlane_x;
	double 	s;

	oldDir_x = params->dir.x;
	oldPlane_x = params->plane.x;
	s = 0.00005;
	if (prog->keys.LEFT == 1)
	{
		params->dir.x = (params->dir.x * cos(-s)) - (params->dir.y * sin(-s));
		params->dir.y = (oldDir_x * sin(-s)) + (params->dir.y * cos(-s));
		params->plane.x = (params->plane.x * cos(-s)) - (params->plane.y * sin(-s));
		params->plane.y = (oldPlane_x * sin(-s)) + (params->plane.y * cos(-s));
	}
	else if (prog->keys.RIGHT == 1)
	{
		params->dir.x = (params->dir.x * cos(s)) - (params->dir.y * sin(s));
		params->dir.y = (oldDir_x * sin(s)) + (params->dir.y * cos(s));
		params->plane.x = (params->plane.x * cos(s)) - (params->plane.y * sin(s));
		params->plane.y = (oldPlane_x * sin(s)) + (params->plane.y * cos(s));
	}	
}

void ft_move(t_cub *prog, t_render *params)
{
	t_point pos;
	double s;

	pos.x = prog->pos.x;
	pos.y = prog->pos.y;
	s = 0.00005;
	if (prog->keys.W == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x + params->dir.x *s)] != '1')
			prog->pos.x += params->dir.x * s;
		if (prog->map[(int)(pos.y + params->dir.y * s)][(int)pos.x] != '1')
			prog->pos.y += params->dir.y * s;
	}		
	else if (prog->keys.S == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x - params->dir.x * s)] != '1')
			prog->pos.x -= params->dir.x * s;
		if (prog->map[(int)(pos.y - params->dir.y * s)][(int)pos.x] != '1')
			prog->pos.y -= params->dir.y * s;
	}	
}

void	ft_side_dist(t_render *params)
{
	if(params->rayDir.x < 0)
	{
		params->stepX = -1;
		params->sideDist.x = (params->pos.x - params->mapX) * params->deltaDist.x;
	}
	else
	{
		params->stepX = 1;
		params->sideDist.x = (params->mapX + 1.0 - params->pos.x) * params->deltaDist.x;
	}
	if(params->rayDir.y < 0)
	{
		params->stepY = -1;
		params->sideDist.y = (params->pos.y - params->mapY) * params->deltaDist.y;
	}
	else
	{
		params->stepY = 1;
		params->sideDist.y = (params->mapY + 1.0 - params->pos.y) * params->deltaDist.y;
	}
}

int	ft_dda(t_cub *prog, t_render *params)
{
	int hit = 0;

	while(hit == 0)
	{
		if(params->sideDist.x < params->sideDist.y)
		{
			params->sideDist.x += params->deltaDist.x;
			params->mapX += params->stepX;
			params->side = 0;
		}
		else
		{ 
			params->sideDist.y += params->deltaDist.y;
			params->mapY += params->stepY;
			params->side = 1;
		}
		if (params->mapY < 0 || (size_t)params->mapY >= prog->map_h)
			return (0);
		if (params->mapX < 0 || (size_t)params->mapX >= prog->map_w)
			return (0);
		printf("Y: %d, X: %d\n", params->mapY, params->mapX);
		if(prog->map[params->mapY][params->mapX] ==  '1') 
			hit = 1;
	}
	return (1);
}

int	ft_draw_start_end(t_render *params)
{
	int lineHeight;

	if(params->side == 0) 
	  params->perpWallDist = (params->sideDist.x - params->deltaDist.x);
	else          
	  params->perpWallDist = (params->sideDist.y - params->deltaDist.y);
	lineHeight = (int)(HEIGHT / params->perpWallDist);
	params->drawStart = -lineHeight / 2 + HEIGHT / 2;
	if(params->drawStart < 0) 
	  params->drawStart = 0;
	params->drawEnd = lineHeight / 2 + HEIGHT / 2;
	if(params->drawEnd >= HEIGHT) 
		params->drawEnd = HEIGHT - 1;
	return (lineHeight);
}

int	ft_texnum(t_render *params)
{
	if (params->side == 0)
	{
		if (params->rayDir.x > 0)
			return (EA);
		else
			return (WE);
	}
	else
	{
		if (params->rayDir.y > 0)
			return (NO);
		else
			return (SO);
	}
}

double	ft_wallx(t_render *params)
{
	double	wallX;

	if (params->side == 0)
		wallX = params->pos.y + params->perpWallDist * params->rayDir.y;
	else
		wallX = params->pos.x + params->perpWallDist * params->rayDir.x;
	wallX -= floor((wallX));
	return (wallX);
}

void	ft_draw_lines(t_cub *prog, t_render *params, int lineHeight, int x)
{
	int		color;
	double	step;
	double	texPos;
	int		texNum;

	texNum = ft_texnum(params);
	prog->texX = (int)(ft_wallx(params) * (double)prog->tex[texNum].w);
	if(params->side == 0 && params->rayDir.x > 0)
		prog->texX = prog->tex[texNum].w - prog->texX - 1;
	if(params->side == 1 && params->rayDir.y < 0)
		prog->texX = prog->tex[texNum].w - prog->texX - 1;
	step = 1.0 * prog->tex[texNum].h / lineHeight;
	texPos = (params->drawStart - HEIGHT / 2 + lineHeight / 2) * step;
	vertical_line(x, 0, params->drawStart, *prog);
	vertical_line(x, params->drawEnd, HEIGHT, *prog);
	while (params->drawStart < params->drawEnd)
	{
		prog->texY = (int)texPos & (prog->tex[texNum].h - 1);
		texPos += step;
		color = get_pixel_color(&prog->tex[texNum].img, prog->texX, prog->texY);
		if(params->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&(prog->img), x, params->drawStart, color);
		params->drawStart++;
	}
}

int	ft_loop_render(t_cub *prog, t_render *params, int x)
{
	int lineHeight;

	ft_side_dist(params);
	if (!ft_dda(prog, params))
		return (0);
	lineHeight = ft_draw_start_end(params);
	ft_draw_lines(prog, params, lineHeight, x);
	ft_rotate(prog, params);
	ft_move(prog, params);
	return (1);
}

void ft_init_render(t_cub *prog, t_render *params, int x)
{
	double cameraX; //x-coordinate in camera space

	cameraX = 2 * x / (double)WIDTH - 1;
	params->pos.x = prog->pos.x + 0.5;
	params->pos.y = prog->pos.y + 0.5;  //x and y start position
	params->rayDir.x = params->dir.x + params->plane.x * cameraX;
	params->rayDir.y = params->dir.y + params->plane.y * cameraX;
	params->mapX = (int) params->pos.x;
	params->mapY = (int) params->pos.y;
	if (params->rayDir.x == 0)
		params->deltaDist.x = 1e30;
	else
		params->deltaDist.x = ft_abs(1 / params->rayDir.x);
	if (params->rayDir.y == 0)
		params->deltaDist.y = 1e30;
	else
		params->deltaDist.y = ft_abs(1 / params->rayDir.y);
}

int ft_start(t_cub *prog)
{
	t_render	*params;

	params = prog->params;
	ft_bzero(prog->img.addr, WIDTH * HEIGHT * (prog->img.bits_per_pixel / 8));
	for(int x = 0; x < WIDTH; x++)
	{
		ft_init_render(prog, params, x);
		if (!ft_loop_render(prog, params, x))
			exit(0);
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	return (1);
}

