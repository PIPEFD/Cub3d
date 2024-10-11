/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:05:03 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:39:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int ft_ischarset(char c, const char *set)
{
    int i;

    i = 0;
    while (*(set + i))
    {
        if(*(set + i) == c)
                return(1);
        i++;
        
    }
    return(0);
}