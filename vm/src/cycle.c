/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamak <msamak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 22:52:28 by msamak            #+#    #+#             */
/*   Updated: 2018/10/05 14:47:32 by msamak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		cycle(t_global *info)
{
	info->clock.cycle++;
	info->clock.current_cycle++;
	if (info->clock.current_cycle == info->clock.cycle_to_die)
	{
		info->clock.cycle_to_die = info->clock.cycle_to_die - CYCLE_DELTA;
		if (info->clock.cycle_to_die < 0)
			info->clock.cycle_to_die = 0;
		info->clock.current_cycle = 0;
	}
	if (info->clock.cycle_to_die <= 0)
		return (1);
	return (0);
}
