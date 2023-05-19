/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:20:28 by handler           #+#    #+#             */
/*   Updated: 2022/11/09 13:54:42 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)destination;
	s = (unsigned char *)source;
	i = -1;
	while (++i < size)
		d[i] = s[i];
	return (destination);
}
// #include <stdio.h>
// #include "libft.h"
// #include <string.h>
// 
// int main() {
// 
// int array [] = { 54, 85, 20, 63, 21 };
// int * copy = NULL;
// int length = sizeof( int ) * 5;
//    
// /* Memory allocation and copy */
// copy = (int *) malloc( length );
// ft_memcpy( copy, array, length );
	// 
// /* Display the copied values */
// for( length=0; length<5; length++ ) {
	// printf( "%d ", copy[ length ] );
// }
// printf( "\n" );
	// 
// free( copy );
// 
// return EXIT_SUCCESS;
// }