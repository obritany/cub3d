/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:46:23 by obritany          #+#    #+#             */
/*   Updated: 2021/03/06 17:46:25 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		print_error(int error)
{
	if (error == -1)
		ft_putstr_fd("Error\nRead file problem\n", 2);
	if (error == -2)
		ft_putstr_fd("Error\nResolution problem\n", 2);
	if (error == -3)
		ft_putstr_fd("Error\nMap problem\n", 2);
	if (error == -4)
		ft_putstr_fd("Error\nColors problem\n", 2);
	if (error == -5)
		ft_putstr_fd("Error\nTexture problem\n", 2);
	if (error == -6)
		ft_putstr_fd("Error\nMalloc problem\n", 2);
	if (error == -7)
		ft_putstr_fd("Error\nData format problem\n", 2);
	if (error == -8)
		ft_putstr_fd("Error\nResolution problem\n", 2);
	if (error == -9)
		ft_putstr_fd("Error\nPosition problem\n", 2);
	if (error == -10)
		ft_putstr_fd("Error\nArguments problem\n", 2);
	return (-1);
}

int		ft_atoi_line(char *line, int *i)
{
	int	rslt;

	rslt = 0;
	skip_space(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		rslt = rslt * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (rslt);
}

int		skip_space(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= '\t' && line[*i] <= '\r'))
		(*i)++;
	return (1);
}
