/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:02:13 by mclerico          #+#    #+#             */
/*   Updated: 2022/09/15 18:02:19 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_close(t_cub *cub)
{
	ft_free_all(cub);
	exit(0);
	return (1);
}

int	ft_hooks_press(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
		ft_close(vars);
	if (keycode == KEY_RIGHT)
		vars->keys.right = 1;
	else if (keycode == KEY_LEFT)
		vars->keys.left = 1;
	else if (keycode == KEY_W)
		vars->keys.w = 1;
	else if (keycode == KEY_S)
		vars->keys.s = 1;
	else if (keycode == KEY_A)
		vars->keys.a = 1;
	else if (keycode == KEY_D)
		vars->keys.d = 1;
	return (0);
}

int	ft_hooks_release(int keycode, t_cub *vars)
{
	if (keycode == KEY_RIGHT)
		vars->keys.right = 0;
	else if (keycode == KEY_LEFT)
		vars->keys.left = 0;
	else if (keycode == KEY_W)
		vars->keys.w = 0;
	else if (keycode == KEY_S)
		vars->keys.s = 0;
	else if (keycode == KEY_A)
		vars->keys.a = 0;
	else if (keycode == KEY_D)
		vars->keys.d = 0;
	return (0);
}
