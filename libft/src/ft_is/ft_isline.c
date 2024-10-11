/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:45:07 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:39:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int ft_isline(char *string)
{
    if(string == NULL)
        return (0);
    while (*string)
    {
        if (*string == '\n')
                return (1);
        string++;                
    }
    return(0);
}