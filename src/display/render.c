#include <cub3d.h>

double	ft_abs(double num)
{
	if (num > 0)
		return num;
	return num*-1;
}

void	ft_side_dist(t_render *params)
{
	if(params->ray_dir.x < 0)
	{
		params->step_x = -1;
		params->side_dist.x = (params->pos.x - params->map_x) * params->delta_dist.x;
	}
	else
	{
		params->step_x = 1;
		params->side_dist.x = (params->map_x + 1.0 - params->pos.x) * params->delta_dist.x;
	}
	if(params->ray_dir.y < 0)
	{
		params->step_y = -1;
		params->side_dist.y = (params->pos.y - params->map_y) * params->delta_dist.y;
	}
	else
	{
		params->step_y = 1;
		params->side_dist.y = (params->map_y + 1.0 - params->pos.y) * params->delta_dist.y;
	}
}

int	ft_dda(t_cub *prog, t_render *params)
{
	int hit = 0;

	while(hit == 0)
	{
		if(params->side_dist.x < params->side_dist.y)
		{
			params->side_dist.x += params->delta_dist.x;
			params->map_x += params->step_x;
			params->side = 0;
		}
		else
		{ 
			params->side_dist.y += params->delta_dist.y;
			params->map_y += params->step_y;
			params->side = 1;
		}
		if (params->map_y < 0 || (size_t)params->map_y >= prog->map_h)
			return (0);
		if (params->map_x < 0 || (size_t)params->map_x >= prog->map_w)
			return (0);
		if(prog->map[params->map_y][params->map_x] ==  '1') 
			hit = 1;
	}
	return (1);
}

int	ft_draw_start_end(t_render *params)
{
	int lineHeight;

	if(params->side == 0) 
	  params->perp_wall_dist = (params->side_dist.x - params->delta_dist.x);
	else          
	  params->perp_wall_dist = (params->side_dist.y - params->delta_dist.y);
	lineHeight = (int)(HEIGHT / params->perp_wall_dist);
	params->draw_start = -lineHeight / 2 + HEIGHT / 2;
	if(params->draw_start < 0) 
	  params->draw_start = 0;
	params->draw_end = lineHeight / 2 + HEIGHT / 2;
	if(params->draw_end >= HEIGHT) 
		params->draw_end = HEIGHT - 1;
	return (lineHeight);
}

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

double	ft_wallx(t_render *params)
{
	double	wallX;

	if (params->side == 0)
		wallX = params->pos.y + params->perp_wall_dist * params->ray_dir.y;
	else
		wallX = params->pos.x + params->perp_wall_dist * params->ray_dir.x;
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
	prog->tex_x = (int)(ft_wallx(params) * (double)prog->tex[texNum].w);
	if(params->side == 0 && params->ray_dir.x > 0)
		prog->tex_x = prog->tex[texNum].w - prog->tex_x - 1;
	if(params->side == 1 && params->ray_dir.y < 0)
		prog->tex_x = prog->tex[texNum].w - prog->tex_x - 1;
	step = 1.0 * prog->tex[texNum].h / lineHeight;
	texPos = (params->draw_start - HEIGHT / 2 + lineHeight / 2) * step;
	vertical_line(x, 0, params->draw_start, *prog);
	vertical_line(x, params->draw_end, HEIGHT, *prog);
	while (params->draw_start < params->draw_end)
	{
		prog->tex_y = (int)texPos & (prog->tex[texNum].h - 1);
		texPos += step;
		color = get_pixel_color(&prog->tex[texNum].img, prog->tex_x, prog->tex_y);
		if(params->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&(prog->img), x, params->draw_start, color);
		params->draw_start++;
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
	params->ray_dir.x = params->dir.x + params->plane.x * cameraX;
	params->ray_dir.y = params->dir.y + params->plane.y * cameraX;
	params->map_x = (int) params->pos.x;
	params->map_y = (int) params->pos.y;
	if (params->ray_dir.x == 0)
		params->delta_dist.x = 1e30;
	else
		params->delta_dist.x = ft_abs(1 / params->ray_dir.x);
	if (params->ray_dir.y == 0)
		params->delta_dist.y = 1e30;
	else
		params->delta_dist.y = ft_abs(1 / params->ray_dir.y);
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

