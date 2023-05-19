/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:48:56 by handler           #+#    #+#             */
/*   Updated: 2022/11/10 18:48:56 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	len_s;
	char			*str;

	i = 0;
	len_s = ft_strlen(s);
	if (len >= len_s)
		len = len_s - start;
	if (start > len_s)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (start < len_s && i < len)
		str[i++] = (char)s[start++];
	str[i] = '\0';
	return (str);
}

// int main (void)
// {
//     printf("1 [%s]\n", ft_substr("tripoulle",0,42000));
//     printf("2 [%s]\n", ft_substr("tripoulle",1,1));
//     printf("3 [%s]\n", ft_substr("tripoulle",100,1));
//     printf("4 [%s]\n", ft_substr("1",42,42000));
//     printf("5 [%s]\n", ft_substr("0123456789",9,10));
//     printf("6 [%s]\n", ft_substr("42",0,0));
//     printf("7 [%s]\n", ft_substr("BONJOUR LES HARICOTS !",8,14));
//     printf("8 [%s]\n", ft_substr("test",1,2));
// }