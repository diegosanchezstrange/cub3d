#include <cub3d.h>
#include <stdio.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;
	int		color;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);	
}

int	ft_bigger(double x, double y)
{
	if (x < y)
		return (1);
	return (-1);
}
/*
void vertical_line(double x, double yi, double yo, int color)
{

}
*/
/*
void	plot_line(t_point p1, t_point p2, t_data img, t_data tex)
{
	t_point	s;
	t_point	d;
	double	err[2];
	int		color;
	t_point	p0;

	//printf("%f, %f\n", p1.y, p2.y);
	s = (t_point){ft_bigger(p1.x, p2.x), ft_bigger(p1.y, p2.y), 0, 0};
	d = (t_point){ft_abs(p2.x - p1.x), ft_abs(p2.y - p1.y) * -1, 0, 0};
	//printf("%f, %f\n", d.x, d.y);
	err[0] = d.x + d.y;
	//printf("error: %f\n",err[0]);
	p0 = p1;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		//printf("traza plot\n");
		color = get_pixel_color(&tex, tex.texX, tex.texY);
		my_mlx_pixel_put(&img, p1.x, p1.y, color);
//		printf("error: %f\n",err[0]);
		err[1] = 2 * err[0];
		if (err[1] >= d.y)
		{
			err[0] += d.y;
			p1.x += s.x;
		}
		if (err[1] <= d.x)
		{
			err[0] += d.x;
			p1.y += s.y;
		}
	}
}*/
