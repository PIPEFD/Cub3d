/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muribe-l <muribe-l@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:53:45 by muribe-l          #+#    #+#             */
/*   Updated: 2024/09/10 14:56:38 by muribe-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubcpy(char *string, int x, int y)
{
	int		i;
	char	*ptr;
	int		len;

	len = y - x;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && *(string + x + i) != '\0')
	{
		*(ptr + i) = *(string + x + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
