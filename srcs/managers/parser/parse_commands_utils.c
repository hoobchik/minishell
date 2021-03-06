/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklotz <mklotz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:05:20 by lmallado          #+#    #+#             */
/*   Updated: 2020/10/17 15:36:19 by mklotz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_command	*catch_endpoint(char *str, int *start, t_main *main)
{
	t_command	*new;
	int			iterator;

	iterator = *start;
	if ((str[iterator] != ';' && is_valid_point_catched(str[iterator])))
		return (NULL);
	if (str[iterator] == ';')
		iterator++;
	while (str[iterator] == ' ')
		iterator++;
	*start = iterator;
	if (str[iterator] == '\0')
		return (get_null_command(4));
	new = create_obj(get_command_str(str, *start, main),
	get_args_str(str, *start, main), 0);
	while (!is_valid_point_catched(str[iterator]) && str[iterator] != '\0')
		iterator++;
	if (str[iterator] == ';')
		iterator++;
	new->endpoint_type = 0;
	*start = iterator;
	return (new);
}

t_command	*catch_pipe(char *str, int *start, t_main *main)
{
	t_command	*new;
	int			iterator;

	iterator = *start;
	if (str[iterator] == '|')
		iterator++;
	else
		return (NULL);
	while (str[iterator] == ' ')
		iterator++;
	*start = iterator;
	if (str[iterator] == '\0')
		return (get_null_command(4));
	new = create_obj(get_command_str(str, *start, main),
	get_args_str(str, *start, main), 0);
	while (!is_valid_point_catched(str[iterator]) && str[iterator] != '\0')
		iterator++;
	*start = iterator;
	new->endpoint_type = 1;
	return (new);
}

t_command	*catch_redirect(char *str, int *start, t_main *main,
t_command *current)
{
	t_command	*new;
	int			iterator;

	iterator = *start;
	if (str[iterator] == '>')
		iterator++;
	else
		return (NULL);
	if (str[iterator] == '>')
		return (NULL);
	while (str[iterator] == ' ')
		iterator++;
	if (str[iterator] == '\0')
		return (get_null_command(4));
	*start = iterator;
	new = create_obj(get_command_str(str, *start, main), NULL, 1);
	join_args(current, get_args_str(str, *start, main));
	while (!is_valid_point_catched(str[iterator]) && str[iterator] != '\0')
		iterator++;
	*start = iterator;
	new->redirect_type = 1;
	new->endpoint_type = 2;
	return (new);
}

t_command	*catch_back_redirect(char *str, int *start, t_main *main,
t_command *current)
{
	t_command	*new;
	int			iterator;

	iterator = *start;
	if (str[iterator] == '<')
		iterator++;
	else
		return (NULL);
	while (str[iterator] == ' ')
		iterator++;
	if (str[iterator] == '\0')
		return (get_null_command(4));
	*start = iterator;
	new = create_obj(get_command_str(str, *start, main), NULL, 1);
	join_args(current, get_args_str(str, *start, main));
	while (!is_valid_point_catched(str[iterator]) && str[iterator] != '\0')
		iterator++;
	*start = iterator;
	new->redirect_type = 3;
	new->endpoint_type = 2;
	return (new);
}

t_command	*catch_double_redirect(char *str, int *start, t_main *main,
t_command *current)
{
	t_command	*new;
	int			iterator;

	iterator = *start;
	if (str[iterator] == '>' && str[iterator + 1] == '>')
		iterator += 2;
	else
		return (NULL);
	while (str[iterator] == ' ')
		iterator++;
	if (str[iterator] == '\0')
		return (get_null_command(4));
	*start = iterator;
	new = create_obj(get_command_str(str, *start, main), NULL, 1);
	join_args(current, get_args_str(str, *start, main));
	while (!is_valid_point_catched(str[iterator]) && str[iterator] != '\0')
		iterator++;
	*start = iterator;
	new->redirect_type = 2;
	new->endpoint_type = 2;
	return (new);
}
