/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:42:24 by kabasolo          #+#    #+#             */
/*   Updated: 2024/10/09 10:06:10 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	int		px;
	int		py;
	int		dir;
	
	char	*north_file;
	char	*south_file;
	char	*east_file;
	char	*west_file;
	void	*north_texture;
	void	*south_texture;
	void	*east_texture;
	void	*west_texture;

	int		ceiling[3];
	int		floor[3];
	char	**map;
}	t_data;

#endif //STRUCTS_H