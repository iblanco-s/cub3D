/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:12:32 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 11:33:59 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data.texture_list = NULL;
	parse(argc, argv, &data, data.texture_list);
	// raycasting(data);
	exec(&data);
	return (0);
}
