/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:31:29 by dsanchez          #+#    #+#             */
/*   Updated: 2022/07/23 18:37:51 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>

int	ft_hooks(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
	{
		//ft_free_all(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		//free(vars.mlx);
		exit(0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	prog;
	int		i;

	i = 0;
	char *str;

	str = calloc(0, sizeof(char));
	free(str);
	free(str);
	if (argc != 2)
		return (1);
	prog.map = ft_calloc(1, sizeof(char *));
	prog.map[0] = NULL;
	prog.map_w = 0;
	prog.map_h = 0;
	prog.starting_point = 0;
	if (!ft_parse_file(argv[1], &prog))
		return (2);
	while (prog.map[i])
		ft_printf("|%s|\n", prog.map[i++]);
	ft_printf("%d\n", prog.map_w);
	ft_printf("%d\n", prog.map_h);
	ft_printf("%c\n", prog.starting_point);
	//prog.mlx = mlx_init();
	//prog.win = mlx_new_window(prog.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	//mlx_hook(prog.win, 2, 1L << 0, ft_hooks, &prog);
	//mlx_loop(prog.mlx);
	return (0);
}
