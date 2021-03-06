/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklotz <mklotz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:21:12 by lmallado          #+#    #+#             */
/*   Updated: 2020/10/24 15:01:42 by mklotz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int			is_valid_point_catched(char c)
{
	if (c == ';' || c == '|' || c == '<' || c == '>')
		return (1);
	else
		return (0);
}

t_command	*get_null_command(int undef)
{
	t_command	*new;

	new = create_obj(NULL, NULL, 0);
	new->undefined_arg = undef;
	return (new);
}

int			check_parser_error(t_command *start, t_command *current, int mode)
{
	if (current == NULL || current->undefined_arg != 0)
	{
		send_custom_error("Double cuote or something like this catched");
		free_command_list(start);
		if (mode == 1)
			free_command_list(current);
		return (1);
	}
	return (0);
}

void		free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void		free_command_list(t_command *command)
{
	if (command)
	{
		if (command->command_str)
			free(command->command_str);
		free_args(command->args);
		if (command->pipe)
			free_command_list(command->pipe);
		if (command->redirect)
			free_command_list(command->redirect);
		if (command->next)
			free_command_list(command->next);
		free(command);
	}
}
