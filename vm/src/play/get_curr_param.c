/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <rbarbazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 10:30:07 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/10/27 13:34:42 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** *****************************************************************************
** check if param type found matches
** type is a CODE define and need to be converted to a t_arg_type
** *****************************************************************************
*/

static void	match_param(int type, int i, t_process *process)
{
	int	j;

	j = 0;
	if (!type)
	{
		process->valid_ocp = 0;
		return ;
	}
	else if (type == IND_CODE)
		type = T_IND;
	else if (type == REG_CODE)
		type = T_REG;
	else if (type == DIR_CODE)
		type = T_DIR;
	while (j < 16)
	{
		if (g_op_tab[j].opcode == process->curr_op.opcode)
		{
			if ((g_op_tab[j].param[i] | type) != g_op_tab[j].param[i])
				process->valid_ocp = 0;
			process->type_param[i] = type;
		}
		j++;
	}
}

/*
** *****************************************************************************
** apply mask coresponding to the current param to find its type
** *****************************************************************************
*/

static int	parse_ocp(unsigned char ocp, int i)
{
	int	type;

	type = 0;
	if (!i)
		type = (ocp & 192) >> 6;
	else if (i == 1)
		type = (ocp & 48) >> 4;
	else if (i == 2)
		type = (ocp & 12) >> 2;
	return (type);
}

/*
** *****************************************************************************
** case no ocp : get one param
** *****************************************************************************
*/

static void	without_ocp(t_global *info, t_process *process)
{
	char	*param;
	int		size;

	if (process->curr_op.opcode == 1)
		size = 4;
	else
		size = 2;
	param = get_value_at_position(info->map, process->curr_pos, size);
	process->type_param[0] = T_DIR;
	process->curr_op.param[0] = tab_to_int(param);
	process->curr_op.param[1] = 0;
	process->curr_op.param[2] = 0;
	ft_strdel(&param);
	increase_position(process, size);
}

/*
** *****************************************************************************
** check the ocp and get the param according to their size
** *****************************************************************************
*/

static void	with_ocp(t_global *info, t_process *process, unsigned char ocp)
{
	int		i;
	int		type;
	char	*value;
	int		size;

	i = 0;
	size = 0;
	if ((ocp & 3) != 0)
		process->valid_ocp = 0;
	while (i < process->curr_op.nb_param)
	{
		type = parse_ocp(ocp, i);
		match_param(type, i, process);
		if (type == REG_CODE)
			size = 1;
		else if ((type == DIR_CODE && process->curr_op.nb_or_address)\
			|| type == IND_CODE)
			size = 2;
		else if (type == DIR_CODE && !process->curr_op.nb_or_address)
			size = 4;
		value = get_value_at_position(info->map, process->curr_pos, size);
		process->curr_op.param[i++] = tab_to_int(value);
		ft_strdel(&value);
		increase_position(process, size);
	}
}

void		get_op_param(t_global *info, t_process *process, unsigned char ocp)
{
	if (process->curr_op.has_ocp)
	{
		increase_position(process, 1);
		with_ocp(info, process, ocp);
	}
	else
		without_ocp(info, process);
}
