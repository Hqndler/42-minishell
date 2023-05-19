/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:30:53 by handler           #+#    #+#             */
/*   Updated: 2023/05/08 11:28:06 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	list_new_elem_str(t_list_gnl **new, char *elem)
{
	(*new) = malloc(sizeof(t_list_gnl));
	if (*new == NULL)
		return (0);
	(*new)->content = elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	add_to_list_gnl(t_list_gnl **list, char *buf)
{
	t_list_gnl	*new;

	if (!list_new_elem_str(&new, buf))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

int	free_list_gnl(t_list_gnl **list)
{
	t_list_gnl	*tmp;
	t_list_gnl	*current;

	current = *list;
	if (!*list)
		return (0);
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->content);
		free(tmp);
	}
	free(current->content);
	free(current);
	*list = NULL;
	return (0);
}

int	write_in_list_gnl(int fd, t_list_gnl **list)
{
	char	*buf;
	int		r_res;

	r_res = 1;
	while (!new_line(*list) && r_res != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (free_list_gnl(list));
		r_res = read(fd, buf, BUFFER_SIZE);
		if (r_res <= 0 && !(*list))
		{
			free(buf);
			return (free_list_gnl(list));
		}
		buf[r_res] = '\0';
		if (!add_to_list_gnl(list, buf))
		{
			free(buf);
			return (free_list_gnl(list));
		}
	}
	return (1);
}

int	clear_list_gnl(t_list_gnl **list)
{
	t_list_gnl	*last;
	char		*content;
	int			i;
	int			j;

	if (!list)
		return (0);
	last = (*list)->prev;
	i = 0;
	while (last -> content[i] != '\n' && last -> content[i])
		i++;
	if (last -> content[i] == '\n' && last -> content[i])
		i++;
	j = ft_strlen(last -> content);
	content = malloc(sizeof(char) * ((j - i) + 1));
	if (!content)
		return (free_list_gnl(list));
	j = 0;
	while (last -> content[i])
		content[j++] = last -> content[i++];
	content[j] = '\0';
	free_list_gnl(list);
	add_to_list_gnl(list, content);
	return (1);
}
