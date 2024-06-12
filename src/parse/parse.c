/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:52:44 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/12 12:21:51 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_error(char *str)
{
	write(2, str++, 1);
	return (1);
}

int	parse(int argc, char **argv, t_data *data)
{
	int	count;

	if (argc != 2 || !check_extension(argv[1]))
	{
		ft_error("Error: Wrong argument\n");
		exit(0);
	}
}
