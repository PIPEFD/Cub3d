/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:34:05 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/01 12:12:06 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



t_data	*parsing(char *file_name)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->map = get_map(file_name);
	if (!valid_map(data->map))
		return (free_data(data), NULL);
	if (!get_player_data(data))
		return (free_data(data), NULL);
}