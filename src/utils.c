/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:41:41 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/12 15:07:31 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		define_wall(t_wolf *wolf)
{
	if (wolf->orientation == 1)
		wolf->curr_tx = wolf->tx;
	else if (wolf->orientation == 2)
		wolf->curr_tx = wolf->tx + 1;
	else if (wolf->orientation == 3)
		wolf->curr_tx = wolf->tx + 3;
	else
		wolf->curr_tx = wolf->tx + 4;
}

void		define_color(t_wolf *wolf, t_main_window *window)
{
	if (window->y < wolf->line_horizon - window->p / 2)
		window->color = 0xFFFFFF;
	else if (window->y < wolf->line_horizon + window->p / 2)
		window->color = ((int*)wolf->curr_tx->start_img)[(int)window->pos +
			(int)((window->y - wolf->line_horizon + window->p / 2) /
				window->p * wolf->curr_tx->heidth) * wolf->curr_tx->width];
	else
		window->color = 0x666666;
}

void		find_orientation_p(t_orientation *orientation, t_wolf *wolf)
{
	while (orientation->x >= 0 && orientation->x < wolf->width &&
		orientation->y >= 0 && orientation->y < wolf->heigth &&
			wolf->orientation == 0)
	{
		if (*(wolf->map + (int)(orientation->x) +
			((int)orientation->y) * wolf->width) != '0')
		{
			wolf->orientation = 3;
			break ;
		}
		if (*(wolf->map + (int)(orientation->x - 1) +
			((int)orientation->y) * wolf->width) != '0')
		{
			wolf->orientation = 1;
			break ;
		}
		orientation->y -= orientation->y_step;
		orientation->x += orientation->x_step;
	}
}

void	find_orientation_p2(t_orientation *orientation, t_wolf *wolf)
{
	while (orientation->x >= 0 && orientation->x < wolf->width &&
		orientation->y >= 0 && orientation->y < wolf->heigth &&
			orientation->orientation == 0)
	{
		if (*(wolf->map + (int)(orientation->x) +
			((int)orientation->y - 1) * wolf->width) != '0')
		{
			orientation->orientation = 2;
			break ;
		}
		if (*(wolf->map + (int)(orientation->x) +
			((int)orientation->y) * wolf->width) != '0')
		{
			orientation->orientation = 4;
			break ;
		}
		orientation->y = orientation->y - orientation->y_step;
		orientation->x = orientation->x + orientation->x_step;
	}
}
