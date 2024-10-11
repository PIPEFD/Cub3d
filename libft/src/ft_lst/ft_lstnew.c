/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 08:49:02 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 18:42:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list *ft_lstnew(void *content)
{
    t_list *new;
    new = (t_list *) malloc (sizeof(t_list));
    if (new == NULL)
        return (NULL);
    new -> content = content;
    new -> next = NULL;
    return (new);
}