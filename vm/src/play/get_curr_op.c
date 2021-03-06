/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamak <msamak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:11:37 by msamak            #+#    #+#             */
/*   Updated: 2018/10/19 13:50:21 by msamak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** *****************************************************************************
** iterates on the op tab to find the coresponding opcode
** stores the number of cycles required
** if no match -> return -1
** *****************************************************************************
*/

int		get_data_from_op(int op, t_process *process)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (g_op_tab[i].opcode == op)
		{
			ft_memcpy(process->curr_op.name, g_op_tab[i].name, 6);
			process->curr_op.nb_param = g_op_tab[i].nb_param;
			process->curr_op.opcode = g_op_tab[i].opcode;
			process->curr_op.cycle = g_op_tab[i].cycle;
			process->curr_op.has_ocp = g_op_tab[i].has_ocp;
			process->curr_op.nb_or_address = g_op_tab[i].nb_or_address;
			return (g_op_tab[i].cycle);
		}
		i++;
	}
	return (-1);
}

char	get_ocp(t_global *info, t_process *process)
{
	char			*value;
	unsigned char	ocp;

	value = get_value_at_position(info->map, process->curr_pos, 1);
	ocp = (unsigned char)value[3];
	ft_strdel(&value);
	return (ocp);
}

void	increase_position(t_process *process, unsigned int add)
{
	process->pc += add;
	process->curr_pos = process->start_pos + process->pc;
	process->curr_pos %= MEM_SIZE;
}

/*
** *****************************************************************************
** gets the current opcode and check if it is valid
** *****************************************************************************
*/

void	get_op(t_global *info, t_process *process)
{
	unsigned char	ocp;

	ocp = 0;
	process->valid_ocp = 1;
	process->op_pos = process->curr_pos;
	process->op_pc = process->pc;
	increase_position(process, 1);
	process->cycle_left--;
	if (process->curr_op.has_ocp)
		ocp = get_ocp(info, process);
	get_op_param(info, process, ocp);
}
