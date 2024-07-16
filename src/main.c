/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iblanco- <iblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:12:32 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/16 16:10:37 by iblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_data_init(&data);
	if (!parse(argc, argv, &data, data.texture_list))
		return (ft_free_data(&data), 1);
	exec(&data);
}
