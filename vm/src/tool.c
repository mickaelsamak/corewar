/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <rbarbazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:04:01 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/10/27 13:36:19 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			ft_carry(t_process *process, int value)
{
	if (!value)
		process->carry = 1;
	else
		process->carry = 0;
}

/*
** *****************************************************************************
** writes 4 bytes at an absolute on the map
** *****************************************************************************
*/

void			write_at_position(t_map *map, t_process *process,\
	unsigned int position, unsigned int buff)
{
	int			i;
	char		*itoaed;
	t_global	*info;

	info = get_global();
	if (!(itoaed = uitoa_d(buff)))
		exit_corewar(MALLOC_ERROR);
	position %= MEM_SIZE;
	while (map && position)
	{
		map = map->next;
		position--;
	}
	i = 0;
	while (map && i < 4)
	{
		map->c = itoaed[i++];
		map->pnumber = process->op_pnumber;
		map->cycle_written = info->clock.cycle + HIGHLIGHT_TIME;
		map = map->next;
	}
	ft_strdel(&itoaed);
}

/*
** *****************************************************************************
** gets from 1 to 4 bytes from a position on the map
** *****************************************************************************
*/

char			*get_value_at_position(t_map *map, unsigned int position,\
	int size)
{
	char	*ret;
	int		i;

	position %= MEM_SIZE;
	i = 0;
	if (!(ret = ft_strnew(4)))
		exit_corewar(MALLOC_ERROR);
	while ((position + size - 1) > 0)
	{
		map = map->next;
		position--;
		if (i++ == MEM_SIZE)
			break ;
	}
	i = 3;
	while (size)
	{
		ret[i--] = map->c;
		map = map->prev;
		size--;
	}
	return (ret);
}

/*
** *****************************************************************************
** turns the map list into a char*
** *****************************************************************************
*/

char			*map_from_list(t_global *info)
{
	t_map	*tmp_m;
	char	*map;
	int		i;

	tmp_m = info->map;
	if (!(map = ft_strnew(MEM_SIZE)))
		exit_corewar(MALLOC_ERROR);
	i = 0;
	while (map && i < MEM_SIZE && tmp_m)
	{
		map[i++] = tmp_m->c;
		tmp_m = tmp_m->next;
	}
	return (map);
}

/*
** *****************************************************************************
** takes a char[4] and returns an int
** *****************************************************************************
*/

int				tab_to_int(char *str)
{
	int		res;

	res = 0;
	res = 0xFF & (res | str[3]);
	res = 0xFFFF & (res | (str[2] << 8));
	res = 0xFFFFFF & (res | (str[1] << 16));
	res = res | (str[0] << 24);
	return (res);
}
