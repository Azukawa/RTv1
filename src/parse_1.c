/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:11:07 by esukava           #+#    #+#             */
/*   Updated: 2022/02/20 23:06:29 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	print_array(t_doom *doom)
{
	int	i;

	i = 0;
	while (i < doom->scene_len)
	{
		printf("%s\n", doom->scene[i]);
		i++;
	}
}

void	print_stuff(t_doom *doom)
{
	int i = 0;

	printf("scene_len = %d\n", doom->scene_len);
	printf("\nobject_count = %d\n", doom->object_count);
	printf("light\tposx = %f posy = %f posz = %f\n", doom->object[9].pos.x, doom->object[9].pos.y, doom->object[9].pos.z);
	printf("cam\tposx = %f posy = %f posz = %f\n", doom->cam.pos.x, doom->cam.pos.y, doom->cam.pos.z);
	printf("cam\trotx = %f roty = %f rotz = %f\n\n", doom->cam.rot.x, doom->cam.rot.y, doom->cam.rot.z);

	while(i < doom->object_count && i < 9)
	{
		printf("object[%d] type\t= %d\n",i , doom->object[i].type);
		printf("object[%d] posx\t= %f posy = %f posz = %f\n", i, doom->object[i].pos.x, doom->object[i].pos.y, doom->object[i].pos.z);
		printf("object[%d] dirx\t= %f diry = %f dirz = %f\n", i, doom->object[i].dir.x, doom->object[i].dir.y, doom->object[i].dir.z);
		printf("object[%d] r\t= %f\n", i, doom->object[i].r);
		printf("object[%d] mater = %d\n", i, doom->object[i].material);
		printf("object[%d] angle\t= %f\n\n", i, doom->object[i].angle);
		i++;
	}
}

t_bool	saveline(char *ret, char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) < 100)
	{
		while (i < 99 && str[i] != '\0' && str[i] != '\n')
		{
			ret[i] = str[i];
			i++;
		}
		ret[i] = '\0';
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool	parse_light(t_doom *doom, char *str)
{
	int	i;

	i = 0;
	if (str[i++] != 'l')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &doom->object[9].pos.x))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->object[9].pos.y))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->object[9].pos.z))
		return (FALSE);
	return (TRUE);
}

t_bool	readscene(char *str, t_doom *doom)
{
	int		fd;
	int		ret;
	int		i;
	char	*output;

	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	ret = get_next_line(fd, &output);
	while (ret > 0 && i < 100)
	{
		saveline(doom->scene[i], output);
		i++;
		free(output);
		ret = get_next_line(fd, &output);
	}
	doom->scene_len = i;
	return (1);
}

t_bool	parse(char *str, t_doom *doom)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((!readscene(str, doom)) || \
	(!parse_quantity(doom, doom->scene[j++])) || \
	(!parse_light(doom, doom->scene[j++])) || \
	(!parse_c_pos(doom, doom->scene[j++])) || \
	(!parse_c_dir(doom, doom->scene[j++])))
		return (FALSE);
	j++;
	while (i < doom->object_count)
	{
		if ((!parse_type(doom, doom->scene[j++], i, 0)) || \
		(!parse_pos(doom, doom->scene[j++], i)) || \
		(!parse_dir(doom, doom->scene[j++], i)) || \
		(!parse_r(doom, doom->scene[j++], i)) || \
		(!parse_material(doom, doom->scene[j++], i)) || \
		(!parse_angle(doom, doom->scene[j++], i)))
			return (FALSE);
		j++;
		i++;
	}
	print_array(doom);
	print_stuff(doom);
	return (TRUE);
}
