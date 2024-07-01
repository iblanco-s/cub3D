/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalaber <jsalaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:58:13 by jsalaber          #+#    #+#             */
/*   Updated: 2024/07/01 09:45:54 by jsalaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	get_index(char *line, int i)
{
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (i);
}

t_text	*new_texture(char *line)
{
	t_text	*list;

	list = (t_text *)ft_calloc(sizeof(t_text), 1);
	if (!list)
		return (NULL);
	while (*line == ' ' || (*line >= 9 && *line <= 13))
		line++;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		list->value = ft_substr(line, 0, 2);
		list->path = ft_substr(line, get_index(line, 2), ft_strlen(line));
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		list->value = ft_substr(line, 0, 1);
		list->path = ft_substr(line, get_index(line, 1), ft_strlen(line));
	}
	list->next = NULL;
	return (list);
}

void	last_texture(t_text **mlx_texture, t_text *new)
{
	t_text	*tmp;

	tmp = *mlx_texture;
	if (*mlx_texture == NULL)
	{
		*mlx_texture = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_list_texture(t_data *data, t_text **mlx_texture)
{
	int		i;
	t_text	*new;

	i = 0;
	while (data->split_texture[i])
	{
		new = new_texture(data->split_texture[i++]);
		if (!new)
			return (0);
		last_texture(mlx_texture, new);
	}
	return (1);
}
