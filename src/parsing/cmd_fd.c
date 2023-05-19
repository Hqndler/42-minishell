/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: handler <handler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:04:15 by reldnah           #+#    #+#             */
/*   Updated: 2023/05/11 22:49:07 by handler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_file(t_data *data, char *filename, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = here_doc(data, filename);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

static bool	get_in(t_data *data, t_token *tmp, t_cmd *cmd)
{
	if (tmp->type == INPUT)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		cmd->infile = open_file(data, tmp->next->str, INPUT);
		if (cmd->infile == -1)
			return (false);
	}
	else if (tmp->type == HEREDOC)
	{
		if (cmd->infile >= 0)
			close(cmd->infile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		cmd->infile = open_file(data, tmp->next->str, HEREDOC);
		if (cmd->infile == -1)
			return (false);
	}
	return (true);
}

bool	get_infile(t_data *data, t_token *token, t_cmd *cmd)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_in(data, tmp, cmd))
		return (false);
	if (tmp->type == PIPE)
		return (true);
	tmp = tmp->next;
	while (tmp->type != PIPE && tmp != data->token)
	{
		if (!get_in(data, tmp, cmd))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

static bool	get_out(t_token *tmp, t_cmd *cmd, t_data *data)
{
	if (tmp->type == TRUNC)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		cmd->outfile = open_file(NULL, tmp->next->str, TRUNC);
		if (cmd->outfile == -1)
			return (false);
	}
	else if (tmp->type == APPEND)
	{
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (tmp == tmp->next || tmp->next->type <= 5)
			return (print_error_token(tmp, data));
		cmd->outfile = open_file(NULL, tmp->next->str, APPEND);
		if (cmd->outfile == -1)
			return (false);
	}
	return (true);
}

bool	get_outfile(t_token *token, t_cmd *cmd, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type != PIPE && !get_out(tmp, cmd, data))
		return (false);
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (!get_out(tmp, cmd, data))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
