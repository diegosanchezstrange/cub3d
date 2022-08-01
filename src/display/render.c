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

void ft_rotate(t_cub *prog)
{
	double	oldDir_x;
	double	oldPlane_x;
	double 	s;

	oldDir_x = prog->dir.x;
	oldPlane_x = prog->plane.x;
	s = 0.00005;
	if (prog->keys.LEFT == 1)
	{
		prog->dir.x = (prog->dir.x * cos(-s)) - (prog->dir.y * sin(-s));
		prog->dir.y = (oldDir_x * sin(-s)) + (prog->dir.y * cos(-s));
		prog->plane.x = (prog->plane.x * cos(-s)) - (prog->plane.y * sin(-s));
		prog->plane.y = (oldPlane_x * sin(-s)) + (prog->plane.y * cos(-s));
	}
	else if (prog->keys.RIGHT == 1)
	{
		prog->dir.x = (prog->dir.x * cos(s)) - (prog->dir.y * sin(s));
		prog->dir.y = (oldDir_x * sin(s)) + (prog->dir.y * cos(s));
		prog->plane.x = (prog->plane.x * cos(s)) - (prog->plane.y * sin(s));
		prog->plane.y = (oldPlane_x * sin(s)) + (prog->plane.y * cos(s));
	}	
}

void ft_move(t_cub *prog)
{
	t_point pos;
	double s;

	pos.x = prog->pos.x;
	pos.y = prog->pos.y;
	s = 0.00005;
	if (prog->keys.W == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x + prog->dir.x *s)] == '0')
			prog->pos.x += prog->dir.x * s;
		if (prog->map[(int)(pos.y + prog->dir.y * s)][(int)pos.x] == '0')
			prog->pos.y += prog->dir.y * s;
	}		
	else if (prog->keys.S == 1)
	{
		if (prog->map[(int)pos.y][(int)(pos.x - prog->dir.x * s)] == '0')
			prog->pos.x -= prog->dir.x * s;
		if (prog->map[(int)(pos.y - prog->dir.y * s)][(int)pos.x] == '0')
			prog->pos.y -= prog->dir.y * s;
	}	
}

void initialize_pos(t_cub *prog)
{
	prog->dir.x =0;
	prog->dir.y = -1; //initial direction vector
	prog->plane.x= 0.66;
	prog->plane.y = 0; //the 2d raycaster version of camera plane
}

int ft_start(t_cub *prog)
{
	t_point pos;
	t_point pi, po;
	t_point dist[2]; // 0 is delta 1 is side
	int mapY, mapX;
	t_point rayDir;
	double perpWallDist;

	ft_bzero(prog->img.addr, WIDTH * HEIGHT * (prog->img.bits_per_pixel / 8));
	pos.x = prog->pos.x + 0.5;
	pos.y = prog->pos.y + 0.5;  //x and y start position
	for(int x = 0; x < WIDTH; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
		rayDir.x = prog->dir.x + prog->plane.x * cameraX;
		rayDir.y = prog->dir.y + prog->plane.y * cameraX;

		mapX = (int) pos.x;
		mapY = (int) pos.y;

		dist[0].x= (rayDir.x == 0) ? 1e30 : ft_abs(1 / rayDir.x);
		dist[0].y= (rayDir.y == 0) ? 1e30 : ft_abs(1 / rayDir.y);

      int stepX;
      int stepY;
      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDir.x < 0)
      {
        stepX = -1;
        dist[1].x = (pos.x - mapX) * dist[0].x;
      }
      else
      {
        stepX = 1;
        dist[1].x = (mapX + 1.0 - pos.x) * dist[0].x;
      }
      if(rayDir.y < 0)
      {
        stepY = -1;
        dist[1].y = (pos.y - mapY) * dist[0].y;
      }
      else
      {
        stepY = 1;
        dist[1].y = (mapY + 1.0 - pos.y) * dist[0].y;
      }
      while(hit == 0)
      {
        if(dist[1].x < dist[1].y)
        {
          dist[1].x += dist[0].x;
          mapX += stepX;
          side = 0;
        }
        else
        { dist[1].y += dist[0].y;
          mapY += stepY;
          side = 1;
        }
        if(prog->map[mapY][mapX] ==  '1') 
			hit = 1;
      }
      if(side == 0) 
		  perpWallDist = (dist[1].x - dist[0].x);
      else          
		  perpWallDist = (dist[1].y - dist[0].y);

      int lineHeight = (int)(HEIGHT / perpWallDist);
      int drawStart = -lineHeight / 2 + HEIGHT / 2;
      if(drawStart < 0) 
		  drawStart = 0;
      int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) 
			drawEnd = HEIGHT - 1;
		if(prog->map[mapY][mapX] == '1')
		pi.x = po.x = x;
		pi.y = drawStart;
		po.y = drawEnd;
		int texNum = 0;
		if (side == 0)
			texNum = 1;
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = pos.y + perpWallDist * rayDir.y;
		else
			wallX = pos.x + perpWallDist * rayDir.x;
		wallX -= floor((wallX));
		prog->texX = (int)(wallX * (double)prog->tex[texNum].w);
		if(side == 0 && rayDir.x > 0)
			prog->texX = prog->tex[texNum].w - prog->texX - 1;
		if(side == 1 && rayDir.y < 0)
			prog->texX = prog->tex[texNum].w - prog->texX - 1;
		double step = 1.0 * prog->tex[texNum].h / lineHeight;
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		double y = drawStart;
		while (y < drawEnd)
      	{
			prog->texY= (int)texPos & (prog->tex[texNum].h - 1);
			texPos += step;
			int color = get_pixel_color(&prog->tex[texNum].img, prog->texX, prog->texY);
			if(side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&(prog->img), x, y, color);
			y++;
      	}
		ft_rotate(prog);
		ft_move(prog);
	}
	mlx_put_image_to_window(prog->mlx, prog->win, prog->img.img, 0, 0);
	return (1);
}
