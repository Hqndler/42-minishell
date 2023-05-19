/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:30:56 by handler           #+#    #+#             */
/*   Updated: 2022/11/09 14:45:47 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
// #include <stdio.h>
// #include <bsd/string.h>
#include "libft.h"

// size_t	ftt_strlen(const char *s)
// {
// 	unsigned int	i;

// 	i = 0;
// 	while (s[i])
// 		++i;
// 	return (i);
// }

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	j = dest_len;
	if (dest_len < size - 1 && size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
			dest[j++] = src[i++];
		dest[j] = '\0';
	}
	if (dest_len > size)
		dest_len = size;
	return (dest_len + src_len);
}

// int main(int argc, char **argv)
// {
// 	int	truc = atoi(argv[1]);
// 	// char un[]  = "une chaine ";
// 	char un[]  = "01234";
// 	// char deux[] = "une deuxieme";
// 	char deux[] = "56789";
// 	printf("Fonction de base : %ld - %s\n",
// strlcat(un, deux, truc), un);
// 	// char un2[]  = "une chaine ";
// 	char un2[]  = "01234";
// 	// char deux2[] = "une deuxieme";
// 	char deux2[] = "56789";
// 	printf("Fonction recodé avec le fion : %ld - %s\n",
// ft_strlcat(un2, deux2, truc), un2);
// }