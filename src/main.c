/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:12:32 by jsalaber          #+#    #+#             */
/*   Updated: 2024/06/28 11:34:51 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


int	main(int argc, char **argv)
{
	t_data	data;

	data.text = NULL;
	parse(argc, argv, &data, data.text);
	raycasting(data);
	// exec(&data);
	return (0);
}