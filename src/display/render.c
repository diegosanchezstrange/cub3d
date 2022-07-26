#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>

double	ft_abs(double num)
{
	if (num > 0)
		return num;
	return num*-1;
}

void ft_start(t_cub prog)
{
	t_point plane;
	t_point	dir;
	t_point pi, po;
	int		i, hit, stepx, stepy, side, map_x, map_y;
	int color;
	int line_h, draw_start, draw_end;
	double	camera_x, perp_dist;
	t_point dist[2]; // 0 is delta dist & 1 is side dist & 
	t_point	ray;

	plane.x = 0;
	plane.y = 0.66;
	dir.x = 0;
	dir.y=-1;
	i = 0;
	while(i < W)	
	{
		map_x =(int)prog.pos.x;
		map_y = (int)prog.pos.y;
		camera_x = (2 * i)/ (double)W;
		ray.x = dir.x  + plane.x * camera_x;
		ray.y = dir.y  + plane.y * camera_x;
		if (ray.x == 0)
			dist[0].x = 1e-30;
		else
			dist[0].x = ft_abs(ray.y/ray.x);
		if (ray.y == 0)
			dist[0].y = 1e-30;
		else
			dist[0].y = ft_abs(ray.x/ray.y);
		if (ray.x < 0)
		{
			stepx = -1;
			dist[1].x = (prog.pos.x - map_x)*dist[0].x;
		}
		else
		{
			stepx = 1;
			dist[1].x = (map_x + 1 - prog.pos.x)*dist[0].x;
		}
		if(ray.y < 0)
		{
			stepy = -1;
			dist[1].y = (prog.pos.y - map_y)*dist[0].y;
		}
		else
		{
			stepy = 1;
			dist[1].y = (map_y + 1 - prog.pos.y)*dist[0].y;
		}
		while (hit == 0)
		{
			if (dist[1].x < dist[1].y)
			{
				dist[1].x += dist[0].x;
				map_x += stepx;
				side = 0;
			}
			else
			{
				dist[1].y += dist[0].y;
				map_y += stepy;
				side = 1;
			}
			if (prog.map[map_x][map_y] > 0)
				hit = 1;
			ft_printf("HOLAAAAAAAAAAAAA\n");
		}
		if(side == 0)
			perp_dist = dist[1].x - dist[0].x;
		else
			perp_dist = dist[1].y - dist[0].y;
		line_h = (int)(H/ perp_dist);
		draw_start = -1*line_h/2 + H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h/2 + H /2 ;
		if (draw_end >= H)
			draw_end = H -1;
		//Wall color
		if(prog.map[map_x][map_y] == 1)
			color = WALL;
		if (side == 1)
			color = WALL_2;
		pi.x = pi.y = i;
		pi.y = draw_start;
		po.y = draw_end;
		plot_line(pi, po, prog.img, color);
		i++;
	}
	mlx_put_image_to_window(prog.mlx, prog.win, prog.img.img, 0, 0);
}
