/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:02:07 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:42:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t ft_lstsize(t_list *list)
{
    unsigned int count;
    count = 0;
    while (list)
    {
        list = list ->next;
        count++;
    }
    return (count);
}
