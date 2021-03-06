/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamak <msamak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 18:43:40 by msamak            #+#    #+#             */
/*   Updated: 2018/10/31 08:37:14 by rbarbazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** *****************************************************************************
** look for the -dump option
** check if a null or positive number is provided
** *****************************************************************************
*/

static int	check_dump(t_global *info, int *i, char **argv)
{
	unsigned long long	nb;

	if (ft_strequ(argv[*i], "-dump"))
	{
		if (!argv[*i + 1] || argv[*i + 1][0] == '-' || !is_number(argv[*i + 1]))
			exit_corewar(USAGE_ERROR);
		if ((nb = atoull(argv[*i + 1])) > UINT_MAX)
			nb = UINT_MAX;
		info->clock.dump = (unsigned int)nb;
		info->dump = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

/*
** *****************************************************************************
** look for the -n option
** *****************************************************************************
*/

static int	check_pnumber(t_global *info, int *i, char **argv)
{
	long	nb;

	if (ft_strequ(argv[*i], "-n"))
	{
		if (!argv[*i + 1] || !argv[*i + 2] || !is_number(argv[*i + 1]))
			exit_corewar(USAGE_ERROR);
		if ((nb = ft_atol(argv[*i + 1])) > MEM_SIZE || nb < -MEM_SIZE || !nb)
			exit_corewar(WRONG_PNUMBER);
		info->next_pnumber = nb;
		(*i) += 2;
		return (1);
	}
	return (0);
}

/*
** *****************************************************************************
** look for the debug option
** *****************************************************************************
*/

static int	check_debug(t_global *info, char *arg)
{
	if (ft_strequ(arg, "--debug"))
	{
		info->debug = 1;
		return (1);
	}
	return (0);
}

/*
** *****************************************************************************
** look for the -v option
** *****************************************************************************
*/

static int	check_visual(t_global *info, char *arg)
{
	if (ft_strequ(arg, "-v"))
	{
		info->visual = 1;
		return (1);
	}
	return (0);
}

/*
** *****************************************************************************
** check how many champions are provided and the options
** *****************************************************************************
*/

int			check_args(t_global *info, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!check_debug(info, argv[i]) && !check_visual(info, argv[i])\
		&& !check_dump(info, &i, argv))
		{
			if (check_pnumber(info, &i, argv))
				check_champ(info, argv[i], 1);
			else
				check_champ(info, argv[i], 0);
		}
		i++;
	}
	if (info->player_count > 4)
		exit_corewar(TOO_MANY_ARGS);
	else if (info->player_count < 1)
		exit_corewar(NO_CHAMP);
	if (info->debug && info->visual)
		exit_corewar(USAGE_ERROR);
	return (0);
}
