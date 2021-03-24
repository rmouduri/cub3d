/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:16:08 by rmouduri          #+#    #+#             */
/*   Updated: 2021/03/24 13:59:23 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_defines.h"

void	fill_line(t_game *game, t_camera *cam, int x, t_img img)
{
	int	y;

	y = -1;
	while (++y < cam->drawstart)
		my_mlx_pixel_put(&game->img, x, y, game->cub.ceiling_color);
	cam->step = 1.0 * img.height / cam->lineheight;
	cam->texpos = (cam->drawstart - game->h / 2 + cam->lineheight / 2) *
		cam->step;
	while (y < cam->drawend)
	{
		cam->texy = (int)cam->texpos & (img.height - 1);
		cam->texpos += cam->step;
		my_mlx_pixel_put(&game->img, x, y, *(int *)(img.addr +
													(cam->texy *
													img.line_length +
													cam->texx *
													(img.bpp /
													8))));
		++y;
	}
	while ((++y - 1) < game->h)
		my_mlx_pixel_put(&game->img, x, y - 1,
						game->cub.floor_color);
}

void	get_wallx_texx(t_player *player, t_camera *cam, t_img img)
{
	if (cam->side == 0)
		cam->wallx = player->posy + cam->perpwalldist * cam->raydiry;
	else
		cam->wallx = player->posx + cam->perpwalldist * cam->raydirx;
	cam->wallx -= cam->wallx < 0 ? (int)cam->wallx - 1 : (int)cam->wallx;
	cam->texx = (int)(cam->wallx * (double)img.width);
	if (cam->side == 0 && cam->raydirx > 0)
		cam->texx = img.width - cam->texx - 1;
	if (cam->side == 1 && cam->raydiry < 0)
		cam->texx = img.width - cam->texx - 1;
}

int		select_texture(t_game *game)
{
	int	index;

	if (game->camera.mapy > game->player.posy && game->camera.side == 1)
		index = EAST;
	else if (game->camera.mapx > game->player.posx && game->camera.side == 0)
		index = SOUTH;
	else if (game->camera.mapy <= game->player.posy && game->camera.side == 1)
		index = WEST;
	else
		index = NORTH;
	return (index);
}

void	get_perp_drawstartend(t_game *game, t_player *player, t_camera *camera)
{
	if (camera->side == 0)
		camera->perpwalldist = (camera->mapx - player->posx
								+ (1 - camera->stepx) /
								2) / camera->raydirx;
	else
		camera->perpwalldist = (camera->mapy - player->posy
								+ (1 - camera->stepy) /
								2) / camera->raydiry;
	camera->lineheight = (int)(game->h / camera->perpwalldist);
	camera->drawstart = -camera->lineheight / 2 + game->h / 2;
	if (camera->drawstart < 0)
		camera->drawstart = 0;
	camera->drawend = camera->lineheight / 2 + game->h / 2;
	if (camera->drawend >= game->h)
		camera->drawend = game->h - 1;
}
