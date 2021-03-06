/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 00:49:55 by rmouduri          #+#    #+#             */
/*   Updated: 2021/04/08 22:07:00 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		line_check(const char *line)
{
	int index;

	index = -1;
	while (line[++index])
		if (line[index] == '1')
			return (1);
	return (0);
}

int		resolution_check(char *line, t_cub *cub, int index)
{
	if ((cub->res_x = ft_atoi(line, &index, 0)) <= 0)
		return (error_code('R'));
	if ((cub->res_y = ft_atoi(line, &index, 0)) <= 0)
		return (error_code('R'));
	while (line[index])
	{
		if ((line[index] != ' ' || line[index] == '\t') && line[index] != '\n')
			return (error_code('R'));
		index++;
	}
	return (1);
}

int		texture_path_check(char *line, t_cub *cub, int index, char orientation)
{
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == '\0')
		return (error_code('T'));
	if (orientation == 'N' && cub->north == NULL)
		cub->north = ft_substr(line, index, ft_strlen(line) - (index));
	else if (orientation == 'S' && cub->south == NULL)
		cub->south = ft_substr(line, index, ft_strlen(line) - (index));
	else if (orientation == 'E' && cub->east == NULL)
		cub->east = ft_substr(line, index, ft_strlen(line) - (index));
	else if (orientation == 'W' && cub->west == NULL)
		cub->west = ft_substr(line, index, ft_strlen(line) - (index));
	else if (orientation == 's' && cub->sprite == NULL)
		cub->sprite = ft_substr(line, index, ft_strlen(line) - (index));
	while (line[index + 1])
	{
		if ((line[index] == ' ' || line[index] == '\t') && (line[index + 1] !=
					' ' && line[index + 1] != '\t' && line[index + 1] != '\n'))
			return (error_code('T'));
		index++;
	}
	return (1);
}

int		floor_check(char *line, t_cub *cub, int index)
{
	if ((cub->floor_color = ft_atoi(line, &index, 255) * 65536) < 0)
		return (error_code('F'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += ft_atoi(line, &index, (cub->floor_color / 256))
	* 256) < 0)
		return (error_code('F'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->floor_color += ft_atoi(line, &index, cub->floor_color)) < 0)
		return (error_code('F'));
	index--;
	while (line[++index])
		if (line[index] != ' ' && line[index] != '\t')
			return (error_code('F'));
	return (1);
}

int		ceiling_check(char *line, t_cub *cub, int index)
{
	if ((cub->ceiling_color = ft_atoi(line, &index, 255) * 65536) < 0)
		return (error_code('C'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += ft_atoi(line, &index, (cub->ceiling_color / 256))
	* 256) < 0)
		return (error_code('C'));
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	if (line[index] == ',')
		index++;
	if ((cub->ceiling_color += ft_atoi(line, &index, cub->ceiling_color)) < 0)
		return (error_code('C'));
	index--;
	while (line[++index])
		if (line[index] != ' ' && line[index] != '\t')
			return (error_code('C'));
	return (1);
}
