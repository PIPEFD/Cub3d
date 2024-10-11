/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:25:34 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:40:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t ft_intlst_size(t_intlst *lst)
{
    size_t  size;

    size = 0;
    while(lst)
    {
        size++;
        lst= lst->next;
    }
    return(size);
}