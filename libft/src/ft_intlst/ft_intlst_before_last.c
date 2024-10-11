/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlst_before_last.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:15:28 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:40:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


t_intlst *ft_intlst_before_last (t_intlst *lst)
{
    if (lst == NULL)
        return (NULL);
    while (lst->next->next)
        lst =lst->next;
    return(lst);
}