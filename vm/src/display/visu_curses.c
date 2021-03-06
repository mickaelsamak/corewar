/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_curses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompagn <lcompagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:54:32 by lcompagn          #+#    #+#             */
/*   Updated: 2018/10/18 18:06:26 by lcompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_curses_cycles(t_global *info)
{
	int		line;
	t_cycle	clock;

	clock = info->clock;
	line = CYCLE_LINE;
	mvprintw(SLEEP_LINE, 2 + 22, "%d   ", info->sleep);
	mvprintw(line, 2 + 14, "        ");
	mvprintw(line++, 2 + 14, "%d", clock.cycle);
	mvprintw(line, 2 + 15, "      ");
	mvprintw(line++, 2 + 15, "%d", clock.current_cycle);
	mvprintw(line, 2 + 15, "      ");
	mvprintw(line, 2 + 15, "%d", clock.cycle_to_die);
}

static int	ft_curses_player(t_global *info)
{
	t_player	*player;
	int			i;

	player = info->player_head;
	i = 1;
	while (player)
	{
		mvprintw(PLAYER_LINE + ((i - 1) * 4) + 1, 2,
		" Last live:\t\t\t%d   ", player->last_live);
		mvprintw(PLAYER_LINE + ((i - 1) * 4) + 2, 2,
		" Lives in current period:\t%d    ", player->curr_live);
		player = player->next;
		i++;
	}
	return (PLAYER_LINE + (4 * (i - 1)));
}

static void	ft_some_usefull_info(t_global *info, int ret)
{
	static int		update = CYCLE_PER_SEC_UPDATE;
	static clock_t	timing = 0;
	double			res;

	mvprintw(++ret, 2, "Processes = %d     ", info->process_count);
	if (update)
		update--;
	else
		update = CYCLE_PER_SEC_UPDATE;
	if (timing == 0)
	{
		timing = clock();
		mvprintw((ret = ret + 2), 2, "Cycle/sec = 0");
	}
	else if (update == CYCLE_PER_SEC_UPDATE)
	{
		res = (double)(1.0 / ((CYCLE_PER_SEC_UPDATE * info->sleep / 1000000.0) \
					+ ((double)(clock() - timing) / CLOCKS_PER_SEC)));
		res = (double)(CYCLE_PER_SEC_UPDATE * res);
		mvprintw((ret = ret + 2), 2, "Cycle/sec = %.1F   ", res);
		timing = clock();
	}
}

int			ft_visu_curses(t_global *info)
{
	static int	first = 1;
	int			ret;

	if (first)
	{
		if (ft_init_curses(info))
			return (0);
		first--;
	}
	ft_curses_cycles(info);
	ret = ft_curses_player(info);
	ft_curses_map(info);
	ft_some_usefull_info(info, ret);
	ft_get_input(info);
	refresh();
	usleep(info->sleep);
	return (SUCCESS);
}
