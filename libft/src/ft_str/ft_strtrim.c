/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:49:58 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:44:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	ptr = ft_substr(s1, 0, len + 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}
// int main(void)
// {
//     char a[] = "hboblbab";
//     char b[] = "h";
//     printf("resultado: %s\n", ft_strtrim(a, b));
//     return(0);
// }