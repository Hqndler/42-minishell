/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:48:42 by handler           #+#    #+#             */
/*   Updated: 2022/11/14 18:12:56 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_sep(char *str, char sep)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == sep)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && in_sep((char *)set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end && in_sep((char *)set, s1[end]))
		end--;
	i = 0;
	if (start > end)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

// int main(void)
// {
//     char s1[] = "    x    x  xxxx   xxx   x x x x x x xxxx x x";
//     printf("[%s]\n", ft_strtrim(s1, " x"));
// }