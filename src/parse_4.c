/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:13:37 by esukava           #+#    #+#             */
/*   Updated: 2022/02/20 22:47:50 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_bool static	str_to_rot(int *i, char *str, float *pos)
{
	char	ret[3];
	int		j;

	ft_bzero(ret, 3);
	j = 0;
	while (str[*i] != ',' && str[*i] != ';' && j < 3)
	{
		if (!ft_isdigit(str[*i]))
			return (FALSE);
		ret[j] = str[*i];
		*i += 1;
		j++;
	}
	*i += 1;
	*pos = ft_clamp_i(ft_atoi(ret), 0, 360);
	if (*pos >= 0 && *pos <= 360)
		return (TRUE);
	return (FALSE);
}

t_bool	parse_c_pos(t_doom *doom, char *str)
{
	int	i;

	i = 0;
	if (str[i++] != 'P')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &doom->cam.pos.x))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->cam.pos.y))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->cam.pos.z))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_c_dir(t_doom *doom, char *str)
{
	int	i;

	i = 0;
	if (str[i++] != 'R')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_rot(&i, str, &doom->cam.rot.x))
		return (FALSE);
	if (!str_to_rot(&i, str, &doom->cam.rot.y))
		return (FALSE);
	if (!str_to_rot(&i, str, &doom->cam.rot.z))
		return (FALSE);
	return (TRUE);
}