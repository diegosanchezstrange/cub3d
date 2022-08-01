#include <cub3d.h>
#include <stdio.h>


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 1920 || y >= 1080 || y < 0 || x < 0)
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
}
*/
/*
void	ft_try_lines(t_coord *matrix, t_prog *f)
{
	int		j;

	j = 0;
	ft_bzero(f->img.addr, W_WINDOW * H_WINDOW * (f->img.bits_per_pixel / 8));
	if (f->move_x == 0 && f->move_y == 0)
		ft_center(matrix, f);
	else
		ft_handle(matrix, f);
	while (j < f->h * f->w)
	{
		if ((j + 1) % f->w != 0)
			plot_line((matrix[j]), (matrix[j + 1]), f->img);
		j++;
	}
	j = 0;
	while (j + f->w < f->h * f->w)
	{
		plot_line((matrix[j]), (matrix[(f->w) + j]), f->img);
		j++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
	ft_legend(f);
}
*/
