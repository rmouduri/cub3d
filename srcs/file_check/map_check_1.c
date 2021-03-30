/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 10:58:26 by cmarien           #+#    #+#             */
/*   Updated: 2021/03/24 13:15:56 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		map_verif(char *line, t_cub *cub)
{
	if (cub->start == 0)
	{
		cub->start = 1;
		cub->str = ft_strndup(line);
		if (cub->str == NULL)
			return (error_code('A'));
	}
	return (1);
}

int		border(int **map, int i, int j, int x)
{
	if (map[j][i] != 32 && map[j][i] != '1')
		return (0);
	else if (map[j][i] == 32)
	{
		if (i == 0)
		{
			if (j == 0)
				if ((map[j + 1][i] != 32 && map[j + 1][i] != '1') ||
					(map[j][i + 1] != 32 && map[j][i + 1] != '1'))
					return (0);
			if (j > 0)
				if ((map[j - 1][i] != 32 && map[j - 1][i] != '1') ||
					(map[j][i + 1] != 32 && map[j][i + 1] != '1'))
					return (0);
			if (border_map_check_2(map, i, j, x) == 0)
				return (0);
		}
	}
	return (1);
}

int		core(int **map, int i, int j, int x)
{
	int t;

	t = map[j][i];
	if (t != '1' && t != '0' && t != 32)
		t = '0';
	if (t != '1')
	{
		if (core_map_check_2(map, i, j, t) == 0)
			return (0);
		if (i == x)
			if ((core_set(map, j + 1, i, t)) == 0 ||
				(core_set(map, j, i - 1, t)) == 0 ||
				(core_set(map, j - 1, i, t)) == 0 || t == '0')
				return (0);
		if (i > 0 && i < x)
			if ((core_set(map, j + 1, i, t)) == 0 ||
				(core_set(map, j, i + 1, t)) == 0 ||
				(core_set(map, j - 1, i, t)) == 0 ||
				(core_set(map, j, i - 1, t)) == 0)
				return (0);
	}
	return (1);
}

int		map_check(t_cub *cub)
{
	int	i;
	int	j;

	j = -1;
	cub->is_player = 0;
	while (++j <= cub->y)
	{
		i = -1;
		while (++i <= cub->x)
			if (cub->map[j][i] != '1')
			{
				if (cub->map[j][i] == 'N' || cub->map[j][i] == 'W' ||
				cub->map[j][i] == 'S' || cub->map[j][i] == 'E')
					pos_edit(cub, j, i);
				if ((j == 0 || j == cub->y) && (border(cub->map, i, j, cub->x))
				== 0)
					return (error_code('M'));
				if (j > 0 && j < cub->y && (core(cub->map, i, j, cub->x)) == 0)
					return (error_code('M'));
			}
	}
	if (cub->is_player == 1)
		return (1);
	return (cub->is_player == 0 ? error_code('P') : error_code('p'));
}

int		map_edit(t_cub *cub)
{
	int	index;
	int	x;
	int y;

	y = -1;
	index = 0;
	while (++y < cub->y)
	{
		x = 0;
		while (x < cub->x)
		{
			if (cub->str[index++] == '\n')
				while (x < cub->x && x > 0)
					cub->map[y][x++] = ' ';
			else
				cub->map[y][x++] = cub->str[index - 1];
		}
	}
	--cub->x;
	--cub->y;
	return (map_check(cub));
}
