/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:32:00 by handler           #+#    #+#             */
/*   Updated: 2022/11/09 13:54:42 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t			pos;
	unsigned char	*tmp;

	tmp = (unsigned char *)memoryBlock;
	pos = -1;
	while (++pos < size)
		if (tmp[pos] == (unsigned char)searchedChar)
			return (&(tmp[pos]));
	return (NULL);
}

// #include <stdio.h>
// #include "libft.h"
// #include <string.h>

// int main() {

//     char data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
//     const unsigned int size = 10;

//     // On recherche une valeur inhéxistante :
//     void * found = ft_memchr( data, 57, size );
//     printf( "57 is %s\n", ( found != NULL ? "found" : "not found" ) );

//     // On recherche une valeur existante :
//     found = ft_memchr( data, 50, size );
//     printf( "50 is %s\n", ( found != NULL ? "found" : "not found" ) );
//     if ( found != NULL ) 
//	   {
//         printf( "La valeur à la position calculée est %d\n",
//	   *((char *) found) );
//     }

//     return EXIT_SUCCESS;
// }