/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:13:40 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 14:03:20 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_d(t_player *player, t_cub cub)
{
	if (player->move_d)
	{
		if (cub.map[(int)(player->posx + player->diry * player->movespeed +
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy + 0.19)] == '0' &&
		cub.map[(int)(player->posx + player->diry * player->movespeed +
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx += player->diry * player->movespeed;
		else if (cub.map[(int)(player->posx - (player->diry < 0 ? -0.2 : 0.2))]
		[(int)(player->posy + 0.19)] == '0' && cub.map[(int)(player->posx -
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx = (int)(player->posx) + (player->diry < 0 ? 0.2 : 0.8);
		if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy -
		player->dirx * player->movespeed - (player->dirx < 0 ? -0.2 : 0.2))] ==
		'0' && cub.map[(int)(player->posx - 0.19)][(int)(player->posy - player->
		dirx * player->movespeed - (player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy -= player->dirx * player->movespeed;
		else if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy +
		(player->dirx < 0 ? -0.2 : 0.2))] == '0' && cub.map[(int)(player->posx
		- 0.19)][(int)(player->posy + (player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy = (int)(player->posy) + (player->dirx < 0 ? 0.8 : 0.2);
	}
}

static void	move_a(t_player *player, t_cub cub)
{
	if (player->move_a)
	{
		if (cub.map[(int)(player->posx - player->diry * player->movespeed -
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy + 0.19)] == '0' &&
		cub.map[(int)(player->posx - player->diry * player->movespeed -
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx -= player->diry * player->movespeed;
		else if (cub.map[(int)(player->posx - (player->diry < 0 ? -0.2 : 0.2))]
		[(int)(player->posy + 0.19)] == '0' && cub.map[(int)(player->posx -
		(player->diry < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx = (int)(player->posx) + (player->diry < 0 ? 0.8 : 0.2);
		if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy +
		player->dirx * player->movespeed + (player->dirx < 0 ? -0.2 : 0.2))] ==
		'0' && cub.map[(int)(player->posx - 0.19)][(int)(player->posy + player->
		dirx * player->movespeed + (player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy += player->dirx * player->movespeed;
		else if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy +
		(player->dirx < 0 ? -0.2 : 0.2))] == '0' && cub.map[(int)(player->posx
		- 0.19)][(int)(player->posy + (player->dirx < 0 ? -0.2 : 0.2))] == '0')
			player->posy = (int)(player->posy) + (player->dirx < 0 ? 0.2 : 0.8);
	}
}

static void	move_s(t_player *player, t_cub cub)
{
	if (player->move_s)
	{
		if (cub.map[(int)(player->posx - player->dirx * player->movespeed -
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy + 0.19)] == '0' &&
		cub.map[(int)(player->posx - player->dirx * player->movespeed -
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx -= player->dirx * player->movespeed;
		else if (cub.map[(int)(player->posx - (player->dirx < 0 ? -0.2 : 0.2))]
		[(int)(player->posy + 0.19)] == '0' && cub.map[(int)(player->posx -
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx = (int)(player->posx) + (player->dirx < 0 ? 0.8 : 0.2);
		if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy -
		player->diry * player->movespeed - (player->diry < 0 ? -0.2 : 0.2))] ==
		'0' && cub.map[(int)(player->posx - 0.19)][(int)(player->posy - player->
		diry * player->movespeed - (player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy -= player->diry * player->movespeed;
		else if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy -
		(player->diry < 0 ? -0.2 : 0.2))] == '0' && cub.map[(int)(player->posx
		- 0.19)][(int)(player->posy - (player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy = (int)(player->posy) + (player->diry < 0 ? 0.8 : 0.2);
	}
}

static void	move_w(t_player *player, t_cub cub)
{
	if (player->move_w)
	{
		if (cub.map[(int)(player->posx + player->dirx * player->movespeed +
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy + 0.19)] == '0' &&
		cub.map[(int)(player->posx + player->dirx * player->movespeed +
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx += player->dirx * player->movespeed;
		else if (cub.map[(int)(player->posx + (player->dirx < 0 ? -0.2 : 0.2))]
		[(int)(player->posy + 0.19)] == '0' && cub.map[(int)(player->posx +
		(player->dirx < 0 ? -0.2 : 0.2))][(int)(player->posy - 0.19)] == '0')
			player->posx = (int)(player->posx) + (player->dirx < 0 ? 0.2 : 0.8);
		if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy +
		player->diry * player->movespeed + (player->diry < 0 ? -0.2 : 0.2))] ==
		'0' && cub.map[(int)(player->posx - 0.19)][(int)(player->posy + player->
		diry * player->movespeed + (player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy += player->diry * player->movespeed;
		else if (cub.map[(int)(player->posx + 0.19)][(int)(player->posy +
		(player->diry < 0 ? -0.2 : 0.2))] == '0' && cub.map[(int)(player->posx
		- 0.19)][(int)(player->posy + (player->diry < 0 ? -0.2 : 0.2))] == '0')
			player->posy = (int)(player->posy) + (player->diry < 0 ? 0.2 : 0.8);
	}
}

int			move(t_player *player, t_cub cub)
{
	move_w(player, cub);
	move_s(player, cub);
	move_a(player, cub);
	move_d(player, cub);
	rot_r(player);
	rot_l(player);
	return (0);
}
