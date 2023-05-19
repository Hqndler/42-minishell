/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:09:55 by handler           #+#    #+#             */
/*   Updated: 2022/11/09 14:33:14 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char *big, int index, char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (big[i + index] == little[i] && big[i + index] && (i + index) < len)
		i++;
	if (little[i])
		return (0);
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && (unsigned char)big[i])
	{
		if (ft_search((char *)big, i, (char *)little, len))
			return ((char *)big + i);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	printf("%s\n", ft_strnstr("Foo Bar Baz", "Bar", 10));
// 	printf("%s\n", strnstr("Foo Bar Baz", "Bar", 10));
// 	// printf("%s\n", strstr("Foo Bar Baz", "Bar"));
// }

// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	char * empty = (char*)"";
// 	char c = 0;
// 	printf("%c\n", c);
// 	printf("%s\n", ft_strnstr(haystack, needle, 0));
// 	printf("%s\n", ft_strnstr(haystack, needle, -1));
// 	printf("%s\n", ft_strnstr(haystack, "a", -1));
// 	printf("%s\n", ft_strnstr(haystack, "c", -1));
// 	printf("%s\n", ft_strnstr(empty, "", -1));
// 	printf("%s\n", ft_strnstr(empty, "", 0));
// 	printf("%s\n", ft_strnstr(empty, "coucou", -1));
// 	printf("%s\n", ft_strnstr(haystack, "aaabc", 5));
// 	printf("%s\n", ft_strnstr(empty, "12345", 5));
// 	printf("%s\n", ft_strnstr(haystack, "abcd", 9));
// 	printf("%s\n", ft_strnstr(haystack, "cd", 8));
// 	printf("%s\n", ft_strnstr(haystack, "a", 1));
// 	printf("%s\n", ft_strnstr("1", "a", 1));
// 	printf("%s\n", ft_strnstr("22", "b", 2));
// 	return (0);
// }