/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junesalaberria <junesalaberria@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:52:44 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/17 11:50:52 by junesalaber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_error(char *str)
{
	while (*str)
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
	count = 0;
	if (!read_map(argv[1], data, &count))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	parse(argc, argv, &data);
	return (0);
}