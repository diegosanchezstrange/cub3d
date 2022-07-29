#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
double	ft_abs(double num)
{
	if (num > 0)
		return num;
	return num*-1;
}


void ft_start(t_cub prog)
{
	double posX = prog.pos.x + 0.5f , posY = prog.pos.y + 0.5f;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	t_point pi, po;


	int mapX = (int) posX;
	int mapY = (int) posY;


    for(int x = 0; x < W; x++)
    {
      //calculate ray position and direction
      double cameraX = (2 * x) / (double)W - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

	  printf("cameraX: %f\n", cameraX);
	  printf("RayDirX: %f\n", rayDirX);
	  printf("RayDirY: %f\n\n", rayDirY);

      //which box of the map we're in
      mapX = (int) posX;
      mapY = (int) posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.
      double deltaDistX = (rayDirX == 0) ? 1e30 : ft_abs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : ft_abs(1 / rayDirY);

	  printf("deltaX : %f \n", deltaDistX);
	  printf("deltaY : %f \n", deltaDistY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
	  printf("sideDistX : %f \n", sideDistX);
	  printf("sideDistY : %f \n", sideDistY);
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        { sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
		printf("MAPX: %d, MAPY: %d\n", mapX, mapY);
		printf("(X, Y): %c\n", prog.map[mapY][mapX]);
        if(prog.map[mapY][mapX] ==  '1') 
			hit = 1;
      }
	  printf("sideDistX : %f \n", sideDistX);
	  printf("sideDistY : %f \n", sideDistY);
	  printf("deltaDistX : %f \n", deltaDistX);
	  printf("deltaDistY : %f \n", deltaDistY);
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) 
		  perpWallDist = (sideDistX - deltaDistX);
      else          
		  perpWallDist = (sideDistY - deltaDistY);

	  printf("Wall Dist: %f, side %d\n", perpWallDist, side);
      //Calculate height of line to draw on screen
      int lineHeight = (int)(H / perpWallDist);
	  printf("Line H: %d\n", lineHeight);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + H / 2;
      if(drawStart < 0) 
		  drawStart = 0;
      int drawEnd = lineHeight / 2 + H / 2;
      if(drawEnd >= H) 
		  drawEnd = H - 1;
	  int color;
	  color = 0;
		if(prog.map[mapY][mapX] == '1')
			color = WALL;
		if (side == 1)
			color = WALL_2;

		pi.x = po.x = x;
		pi.y = drawStart;
		po.y = drawEnd;
		plot_line(pi, po, prog.img, color);
	  printf("x: %d\n", x);
	  printf("drawStart: %d\n", drawStart);
	  printf("drawEnd: %d\n", drawEnd);
	}
  mapX = (int) posX;
  mapY = (int) posY;
	printf("mapX: %d, mapY: %d\n", mapX, mapY);
	printf("START mapX: %d, mapY: %d Dir : %c\n", mapX, mapY, prog.map[mapX][mapY]);
	mlx_put_image_to_window(prog.mlx, prog.win, prog.img.img, 0, 0);
}

/*void ft_start(t_cub prog)
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
	dir.y = -1;
	i = 0;
	hit = 0;
	printf("HOLA\n");
	printf("%d\n", W);
	while(i < (int)W)	
	{
		map_x =(int)prog.pos.x;
		map_y = (int)prog.pos.y;
		camera_x = (2 * i)/ (double)W;
		ray.x = dir.x  + plane.x * camera_x;
		ray.y = dir.y  + plane.y * camera_x;

		if (ray.x == 0)
			dist[0].x = 1e-30;
		else
			dist[0].x = ft_abs(1/ray.x);
		if (ray.y == 0)
			dist[0].y = 1e-30;
		else
			dist[0].y = ft_abs(1/ray.y);

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
			if (prog.map[map_x][map_y] == 1)
				hit = 1;
		}
		if(side == 0)
			perp_dist = dist[1].x - dist[0].x;
		else
			perp_dist = dist[1].y - dist[0].y;
		line_h = (int)(H / perp_dist);
		draw_start = (-1 * line_h) / 2 + H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + H / 2 ;
		if (draw_end >= H)
			draw_end = H -1;
		//Wall color
		if(prog.map[map_x][map_y] == 1)
			color = WALL;
		if (side == 1)
			color = WALL_2;
		printf("TRAZA2\n");
		pi.x = po.x = i;
		pi.y = draw_start;
		po.y = draw_end;
		plot_line(pi, po, prog.img, color);
		i++;
	}
	mlx_put_image_to_window(prog.mlx, prog.win, prog.img.img, 0, 0);
}*/
