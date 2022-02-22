/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:28:59 by esukava           #+#    #+#             */
/*   Updated: 2022/02/22 11:43:30 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	skip_white(int *i, char *str)
{
	while (str[*i] == '\t' || str[*i] == ' ')
		*i += 1;
}

t_bool	parse_quantity(t_doom *doom, char *str)
{
	int	i;

	i = 0;
	if (str[i++] != 'q')
		return (FALSE);
	skip_white(&i, str);
	if (str[i] >= '1' && str[i] <= '9')
	{
		doom->object_count = ft_atoi(&str[i]);
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	parse_type(t_doom *doom, char *str, int index, int i)
{
	if (str[i++] != 't')
		return (FALSE);
	skip_white(&i, str);
	if (str[i] == 's')
	{
		doom->object[index].type = SPHERE;
		return (TRUE);
	}
	else if (str[i] == '^')
	{
		doom->object[index].type = CONE;
		return (TRUE);
	}
	else if (str[i] == 'c')
	{
		doom->object[index].type = CYL;
		return (TRUE);
	}
	else if (str[i] == 'p')
	{
		doom->object[index].type = PLANE;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	val_sym(char c, int i)
{
	if (i == 0)
	{
		if (ft_isdigit(c) || c == '-')
			return (TRUE);
		else
			return (FALSE);
	}
	else
		if (ft_isdigit(c))
			return (TRUE);
	return (FALSE);
}

t_bool	str_to_int(int *i, char *str, float *pos)
{
	char	ret[4];
	int		j;

	ft_bzero(ret, 4);
	j = 0;
	while (str[*i] != ',' && str[*i] != ';')
	{
		if (!val_sym(str[*i], j))
			return (FALSE);
		if (j < 3)
			ret[j] = str[*i];
		*i += 1;
		j++;
	}
	*i += 1;
	*pos = ft_atoi(ret);
	if (*pos >= -99 && *pos <= 99)
		return (TRUE);
	return (FALSE);
}
