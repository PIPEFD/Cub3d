/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:28:07 by dbonilla          #+#    #+#             */
/*   Updated: 2023/10/03 18:45:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	str_len;

	if (!s)
		return (0);
	str_len = ft_strlen((char *)s);
	if (start > str_len)
		return (ft_strdup(""));
	if (str_len - start >= len)
	str = (char *)malloc((len + 1) * sizeof(char));
	else
	{
	str = (char *)malloc((str_len - start + 1) * sizeof(char));
	len = str_len;
	}
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}

// int main()
// {
//     char src[] = "123456";
//     int m = 2;
//     int n = 5;
//     char* dest = ft_substr(src, m, n);
//     printf("%s\n", dest);
//     return 0;
// }