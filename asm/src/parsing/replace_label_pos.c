/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_label_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbazz <rbarbazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:45:06 by rbarbazz          #+#    #+#             */
/*   Updated: 2018/10/04 21:23:33 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	replace_uint(t_asm *champ, unsigned int dec, unsigned int pos)
{
	char			size[5];
	unsigned int	len;

	len = 4;
	size[len] = 0;
	while (len)
	{
		size[len - 1] = dec % 256;
		dec /= 256;
		len--;
	}
	while (len < 4)
		champ->cor_file[pos++] = size[len++];
}

static void	replace_ushort(t_asm *champ, unsigned short dec, unsigned int pos)
{
	char			size[3];
	unsigned int	len;

	len = 2;
	size[len] = 0;
	while (len)
	{
		size[len - 1] = dec % 256;
		dec /= 256;
		len--;
	}
	while (len < 2)
		champ->cor_file[pos++] = size[len++];
}

static void	replace_label_pos(t_asm *champ, t_lab *match, t_lab_pos *lab_pos)
{
	long	value;

	if (match->pos < lab_pos->pos)
	{
		if (lab_pos->size == 2)
			value = USHRT_MAX - (lab_pos->op_pos - match->pos) + 1;
		else
			value = UINT_MAX - (lab_pos->op_pos - match->pos) + 1;
	}
	else
		value = match->pos - lab_pos->op_pos;
	if (lab_pos->size == 2)
		replace_ushort(champ, (unsigned short)value, lab_pos->pos);
	else
		replace_uint(champ, (unsigned int)value, lab_pos->pos);
}

void		check_label_pos(t_asm *champ)
{
	t_lab_pos	*tmp;
	t_lab		*match;

	tmp = champ->lab_pos;
	while (tmp)
	{
		if ((match = check_lab_exist(champ, tmp->name)))
			replace_label_pos(champ, match, tmp);
		else
			error_lab(tmp);
		tmp = tmp->next;
	}
}
