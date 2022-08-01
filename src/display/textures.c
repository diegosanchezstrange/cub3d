#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int load_textures(t_cub *prog, t_text *texture, char *path)
{
	if (!path || ft_strlen(path) == 0)	
		return (0);
	texture->img.img = mlx_xpm_file_to_image(prog->mlx, path, &texture->w, &texture->h);
	if (texture->img.img == NULL)
		return (0);
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	if (texture->img.addr == NULL)
		return (0);
	return (1);
}

void init_textures(t_cub *prog)
{
	if (!load_textures(prog, &prog->tex[0], prog->NO_path) ||
			!load_textures(prog, &prog->tex[1], prog->SO_path) ||
			!load_textures(prog, &prog->tex[2], prog->WE_path) ||
			!load_textures(prog, &prog->tex[3], prog->EA_path))
	{
		return ;
	}
}
